Shader "Fractals/Newtone fractal"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_Area("Area", vector) = (0, 0, 4, 4)
		_MaxIter("Max iterations", float) = 100
		_Color("Color", range(0, 1)) = .5
		_Repeat("Repeat", float) = 1
		_Speed("Speed", range(0, 1)) = .01
		_Radius("Radius", float) = 20
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

			v2f vert (appdata v)
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
			float _R;
			float _I;
			float _ShapeSpeed;
			float _CircleRadius;

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

			float2 powi(float2 z, float power)
			{
				float angle = AngleOf(z);
				return (pow(length(z), power) * float2(cos(power * angle), sin(power * angle))); //z in power _Power
			}

			float2 f(float2 z, float power)
			{
				return powi(z, power) - 1;
			}
			float2 df(float2 z, float power)
			{
				return power * powi(z, power - 1);
			}

			float2 cmult(float2 a, float2 b)
			{
				return float2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
			}

			float2 cdiv(float2 a, float2 b)
			{
				return float2((a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y), (-a.x * b.y + a.y * b.x) / (b.x * b.x + b.y * b.y));
			}

			fixed4 frag(v2f i) : SV_Target
			{
				float2 c = _Area.xy + (i.uv - .5f) * _Area.zw;

				float2 z = c;
				float iter;
				float iter2;
				float2 w;
				float2 roots[3];

				float _R2;
				float _I2;
				float2 RI;

				if (_ShapeSpeed != 0)
				{
					_R2 = _CircleRadius * sin(_Time.y * _ShapeSpeed);
					_I2 = _CircleRadius * cos(_Time.y * _ShapeSpeed);
					RI = float2(_R2, _I2);
				}

				for (iter = 0; (int)iter < (int)_MaxIter; iter++)
				{
					w = z;
					z -= cmult(cdiv(f(z, _Power), df(z, _Power)), float2(1, 0));

					if ((_I != 0) || (_R != 0))
					{
						z -= cmult(cdiv(f(z, _Power), df(z, _Power)), float2(_R, _I));
					}
					else
					{
						z -= cmult(cdiv(f(z, _Power), df(z, _Power)), RI);
					}

					if (length(w - z) < _Radius)
					{
						break;
					}
				}

				if (iter == _MaxIter)
				{
					return 0;
				}

				iter -= (length(z) - _Radius) / (_Radius * _Radius - _Radius); //linear interpolation

				return tex2D(_MainTex, float2(pow(iter / _MaxIter, 1.1) * _Repeat + (_Time.y - 2) * _Speed, _Color));
			}
			ENDCG
		}
	}
}
