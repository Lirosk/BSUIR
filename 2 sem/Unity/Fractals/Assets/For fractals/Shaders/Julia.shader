Shader "Fractals/Julia"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
        _Area("Area", vector) = (0, 0, 4, 4)
        _MaxIter("Max iterations", float) = 100
        _Color("Color", range(0, 1)) = .5
        _Repeat("Repeat", float) = 1
        _Speed("Speed", range(0, 1)) = .01
        _Radius("Max radius of C num", float) = 20
        _Power("Power", float) = 2
        _R("Real part", float) = 0
        _I("Imaginary part", float) = .8
        _ShapeSpeed("Shape speed", float) = .5
        _CircleRadius("Radius variable of circle", float) = .5
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
                float _Radius = 20.;
                float _Power;
                float _R;
                float _I;
                float _ShapeSpeed;
                float _CircleRadius;
                float _R2;
                float _I2;

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
                    float2 c = _Area.xy + (i.uv - .5f) * _Area.zw;

                    float2 RI;

                    if (_ShapeSpeed != 0)
                    {
                        _R2 = _CircleRadius * sin(_Time.y * _ShapeSpeed);
                        _I2 = _CircleRadius * cos(_Time.y * _ShapeSpeed);
                        RI = float2(_R2, _I2);
                    }

                    float2 z = c;
                    float iter;

                    for (iter = 0; iter < _MaxIter; iter++)
                    {
                        if ((_I != 0) || (_R != 0))
                        {
                            z = f(z) + float2(_R, _I);
                        }
                        else
                        {
                            z = f(z) + RI;
                        }

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

                    float4 col = tex2D(_MainTex, float2(sqrt(iter / _MaxIter) * _Repeat + (_Time.y - 2) * _Speed, _Color));

                    return col;
                }
                ENDCG
            }
        }
}
