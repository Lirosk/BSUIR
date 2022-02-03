Shader "Fractals/Mandelbrot"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
        _Area("Area", vector) = (0, 0, 4, 4)
        _MaxIter("Max iterations", float) = 100
        _Color("Color", range(0, 1)) = .5
        _Repeat("Repeat", float) = 1
        _Speed("Speed", range(0, 1)) = .01
        _Radius("Radius", float) = 20
         _Power("Power", float) = 2
    }
        SubShader
        {
            // No culling or depth
            Cull Off ZWrite Off ZTest Always

            Pass
            {
                CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag

                #include "UnityCG.cginc"

                struct appdata
                {
                    float4 vertex : POSITION;
                    float2 uv : TEXCOORD0;
                };

                struct v2f
                {
                    float2 uv : TEXCOORD0;
                    float4 vertex : SV_POSITION;
                };

                v2f vert(appdata v)
                {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex);
                    o.uv = v.uv;
                    return o;
                }

                sampler2D _MainTex;
                float4 _Area;
                float _MaxIter;
                float _Color;
                float _Repeat;
                float _Speed;
                float _Radius;
                float _Power;

                float AngleOf(float2 num)
                {
                    float R = num.x;
                    float I = num.y;

                    if ((R > 0) && (I >= 0))
                    {
                        return (atan(I / R));
                    }
                    else if ((R < 0) && (I >= 0))
                    {
                        return (3.14159 - atan(abs(I / R)));
                    }
                    else if ((R < 0) && (I < 0))
                    {
                        return (3.14159 + atan(abs(I / R)));
                    }
                    else if ((R > 0) && (I < 0))
                    {
                        return (2 * 3.14159 - atan(abs(I / R)));
                    }
                    else if ((R == 0) && (I > 0))
                    {
                        return (3.14159 / 2);
                    }
                    else// if ((R == 0) && (I < 0))
                    {
                        return ((3 / 2) * 3.14159);
                    }
                }

                float2 powi(float2 z)
                {
                    float angle = AngleOf(z);
                    return (pow(length(z), _Power) * float2(cos(_Power * angle), sin(_Power * angle))); //z in power _Power
                }

                float2 f(float2 z)
                {
                    return powi(z);
                }


                fixed4 frag(v2f i) : SV_Target
                {
                    float2 c = (_Area.xy +  (i.uv - .5) * _Area.zw);

                    float2 z;
                    float iter;

                    for (iter = 0; iter < _MaxIter; iter++)
                    {
                        z = f(z) + c;

                        if (length(z) > _Radius)
                        {
                            break;
                        }
                    }

                    if (iter >= _MaxIter)
                    {
                        return 0;
                    }

                    iter -= log2(log(length(z)) / log(_Radius)); //double exponential interpolation

                    return tex2D(_MainTex, float2(sqrt(iter / _MaxIter) * _Repeat + (_Time.y - 2) * _Speed, _Color));
                }
                ENDCG
            }
        }
}
