Shader "Fractal/Mandelbrot"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _MaxIters ("Max iterations", float) = 256
        _Power("Power", float) = 2
        _R("Real part", float)
        _I("Imaginary part", float)
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

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

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
                else if ((R > 0) && (I < 0)) //   (() && ())
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

            float2 f(float z)
            {
                return powi(z);
            }


            sampler2D _MainTex;
            float _MaxIters;
            float _Power;
            float _R;
            float _I;

            fixed4 frag (v2f i) : SV_Target
            {
                fixed4 col = tex2D(_MainTex, i.uv);
                
                float iters = 0;

                for (; iters < _MaxIters; iters++)
                {
                    z = f(z) + float(_R, _I);

                    if (length(z) > 2)
                    {
                        break;
                    }
                }

                if (iters == _MaxIters)
                {
                    return 0;
                }

                return iters/_MaxIters;
            }
            ENDCG
        }
    }
}
