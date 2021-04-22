Shader "Fractals/T-square"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_Area("Area", vector) = (0, 0, 4, 4)
		_MaxIterFBS("Max iterations", float) = 256
		_V1("Vertex 1", vector) = (-10, 10, 0, 0)
		_V2("Vertex 2", vector) = (10, 10, 0, 0)
		_V3("Vertex 3", vector) = (10, -10, 0, 0)
		_V4("Vertex 4", vector) = (-10, -10, 0, 0)
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
			float _MaxIterFBS;
			float4 _V1;
			float4 _V2;
			float4 _V3;
			float4 _V4;

			bool inTriag2(float2 a, float2 b, float2 c, float2 d)
			{
				return	(sign((a.x - d.x) * (b.y - a.y) - (b.x - a.x) * (a.y - d.y)) ==
					sign((b.x - d.x) * (c.y - b.y) - (c.x - b.x) * (b.y - d.y))) &&
					(sign((c.x - d.x) * (a.y - c.y) - (a.x - c.x) * (c.y - d.y)) ==
						sign((b.x - d.x) * (c.y - b.y) - (c.x - b.x) * (b.y - d.y)));
			}

			bool inSquare(float2 v1, float2 v2, float2 v3, float2 v4, float2 d)
			{
				return (inTriag2(v1, v2, v4, d) || inTriag2(v2, v3, v4, d) || inTriag2(v1, v2, v3, d) || inTriag2(v1, v3, v4, d));
			}

			float2 threefouth(float2 a, float2 b)
			{
				return (3 * a + b) / 4;
			}

			float2 onehalf(float2 a, float2 b)
			{
				return (a + b) / 2;
			}

			fixed4 frag(v2f i) : SV_Target
			{
				float2 c = _Area.xy + (i.uv - .5) * _Area.zw;

				float iter;

				float2 v1 = _V1.xy;
				float2 v2 = _V2.xy;
				float2 v3 = _V3.xy;
				float2 v4 = _V4.xy;

				float2 v1v2;
				float2 v2v3;
				float2 v3v4;
				float2 v1v4;
				float2 cntr;

				if (!inSquare(v1, v2, v3, v4, c))
				{
					return 1;
				}

				for (iter = 0; (int)iter < (int)_MaxIterFBS; iter++)
				{
					v1v2 = onehalf(v1, v2);
					v2v3 = onehalf(v2, v3);
					v3v4 = onehalf(v3, v4);
					v1v4 = onehalf(v1, v4);
					cntr = (v1 + v2 + v3 + v4) / 4;

					if (inSquare(
						threefouth(threefouth(v1, v2), threefouth(v4, v3)),
						threefouth(threefouth(v2, v1), threefouth(v3, v4)),
						threefouth(threefouth(v3, v4), threefouth(v2, v1)),
						threefouth(threefouth(v4, v3), threefouth(v1, v2)),
						c)) //center
					{
						return 1;
					}
					else if (inSquare(v1, v1v2, cntr, v1v4, c)) //north-east
					{
						v2 = v1v2;
						v3 = cntr;
						v4 = v1v4;
					}
					else if (inSquare(v1v2, v2, v2v3, cntr, c)) //north-west
					{
						v1 = v1v2;
						v3 = v2v3;
						v4 = cntr;
					}
					else if (inSquare(cntr, v2v3, v3, v3v4, c)) //south-west
					{
						v1 = cntr;
						v2 = v2v3;
						v4 = v3v4;
					}
					else if (inSquare(v1v4, cntr, v3v4, v4, c)) //south-east
					{
						v1 = v1v4;
						v2 = cntr;
						v3 = v3v4;
					}
					else
					{
						return 0;
					}
				}

				return 0;
			}
			ENDCG
		}
	}
}
