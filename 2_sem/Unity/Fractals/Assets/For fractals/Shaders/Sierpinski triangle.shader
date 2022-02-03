Shader "Fractals/Sierpinski triangle"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_Area("Area", vector) = (0, 0, 4, 4)
		_MaxIterSerp("Max iterations", float) = 7
		_V1("Vertex 1", vector) = (10, 0, 0, 0)
		_V2("Vertex 2", vector) = (0, 5.77350269189625, 0, 0)
		_V3("Vertex 3", vector) = (0, -5.77350269189625, 0, 0)
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
			float _MaxIterSerp;
			float4 _V1;
			float4 _V2;
			float4 _V3;

			float g(float2 a, float2 b, float2 d) 
			{
				return ((d.x - a.x) * (b.y - a.y) - (d.y - a.y) * (b.x - a.x));
			}

			bool f(float2 a, float2 b, float2 c, float2 d) 
			{
				return (g(a, b, c) * g(a, b, d) >= 0);
			}

			float2 triagCenter(float2 a, float2 b, float2 c)
			{
				return float2((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
			}

			bool inTriag(float2 a, float2 b, float2 c, float2 d)
			{
				return (f(a, b, c, d) && f(b, c, a, d) && f(c, a, b, d));
			}

			float2 mPoint(float2 a, float2 b)
			{
				return float2((a.x + b.x) / 2, (a.y + b.y) / 2);
			}

			fixed4 frag (v2f i) : SV_Target
			{
				float2 c = _Area.xy + (i.uv - .5f) * _Area.zw;

				_MaxIterSerp += 1;

				float2 v1 = _V1.xy;
				float2 v2 = _V2.xy;
				float2 v3 = _V3.xy;

				//temp vertexes
				float2 tv1 = v1;
				float2 tv2 = v2;
				float2 tv3 = v3;

				if (!inTriag(v1, v2, v3, c))
				{
					return 1;
				}

				float iter;

				for (iter = 0; (int)iter < (int)_MaxIterSerp; iter++)
				{
					if (inTriag(v1, v2, v3, c))
					{
						tv1 = mPoint(v2, v3);
						tv2 = mPoint(v1, v2);
						tv3 = mPoint(v1, v3);

						if (inTriag(tv1, tv2, tv3, c)) //middle triag
						{
							return 1;
						}
						if (inTriag(v1, tv2, tv3, c)) //upper triag
						{
							v2 = tv2;
							v3 = tv3;
						}
						else if (inTriag(tv1, tv2, v2, c)) //right triag
						{
							v1 = tv2;
							v3 = tv1;
						}
						else if (inTriag(tv1, tv3, v3, c)) //left triag
						{
							v1 = tv3;
							v2 = tv1;
						}
						else
						{
							return 0;
						}
					}
				}

				return 0;
			}				
			ENDCG
		}
	}
}
