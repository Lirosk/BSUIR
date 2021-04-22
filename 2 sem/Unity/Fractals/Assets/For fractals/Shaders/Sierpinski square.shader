Shader "Fractals/Sierpinski square"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_Area("Area", vector) = (0, 0, 4, 4)
		_MaxIterSerp("Max iterations", float) = 10
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

		v2f vert(appdata v)
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
			return (inTriag2(v1, v2, v4, d) || inTriag2(v2, v3, v4, d) || inTriag2(v1, v2, v3, d) || inTriag2(v1,v3,v4, d));
		}

		float2 twothird(float2 a, float2 b)
		{
			return (2 * a + b) / 3;
		}		

		fixed4 frag(v2f i) : SV_Target
		{
			float2 c = _Area.xy + (i.uv - .5f) * _Area.zw;

			_MaxIterSerp += 1;

			//vertexes
			float2 v1 = _V1.xy;			
			float2 v2 = _V2.xy;
			float2 v3 = _V3.xy;
			float2 v4 = _V4.xy;

			//temp vertexes
			float2 tv1 = v1;
			float2 tv2 = v2;
			float2 tv3 = v3;
			float2 tv4 = v4;

			//more temp vertexes
			//vertexes for transformation
			float2 ttv1 = v1;
			float2 ttv2 = v2;
			float2 ttv3 = v3;
			float2 ttv4 = v4;

			float iter = 0;

			if (!inSquare(v1, v2, v3, v4, c))
			{
				return 1;
			}		

			for (iter = 0; (int)iter < (int)_MaxIterSerp; iter++)
			{
				tv1 = twothird(twothird(v1, v2), twothird(v4, v3));
				tv2 = twothird(twothird(v2, v1), twothird(v3, v4));
				tv3 = twothird(twothird(v3, v4), twothird(v2, v1));
				tv4 = twothird(twothird(v4, v3), twothird(v1, v2));

				if (inSquare(tv1, tv2, tv3, tv4, c)) //center
				{
					return 1;
				}
				else if (inSquare(v1, twothird(v1, v2), tv1, twothird(v1, v4), c)) //north-west
				{
					ttv2 = twothird(v1, v2);
					ttv3 = tv1;
					ttv4 = twothird(v1, v4);
				}
				else if (inSquare(twothird(v1, v2), twothird(v2, v1), tv2, tv1, c)) //north
				{
					ttv1 = twothird(v1, v2);
					ttv2 = twothird(v2, v1);
					ttv3 = tv2;
					ttv4 = tv1;
				}
				else if (inSquare(twothird(v2, v1), v2, twothird(v2, v3), tv2, c)) //north-east
				{
					ttv1 = twothird(v2, v1);
					ttv3 = twothird(v2, v3);
					ttv4 = tv2;
				}
				else if (inSquare(tv2, twothird(v2, v3), twothird(v3, v2), tv3, c)) //east
				{
					ttv1 = tv2;
					ttv2 = twothird(v2, v3);
					ttv3 = twothird(v3, v2);
					ttv4 = tv3;
				}
				else if (inSquare(tv3, twothird(v3, v2), v3, twothird(v3, v4), c)) //south-east
				{
					ttv1 = tv3;
					ttv2 = twothird(v3, v2);
					ttv4 = twothird(v3, v4);
				}
				else if (inSquare(tv4, tv3, twothird(v3, v4), twothird(v4, v3), c)) //south
				{
					ttv1 = tv4;
					ttv2 = tv3;
					ttv3 = twothird(v3, v4);
					ttv4 = twothird(v4, v3);
				}
				else if (inSquare(twothird(v4, v1), tv4, twothird(v4, v3), v4, c)) //south-west
				{
					ttv1 = twothird(v4, v1);
					ttv2 = tv4;
					ttv3 = twothird(v4, v3);
				}
				else if (inSquare(twothird(v1, v4), tv1, tv4, twothird(v4, v1), c)) //west
				{
					ttv1 = twothird(v1, v4);
					ttv2 = tv1;
					ttv3 = tv4;
					ttv4 = twothird(v4, v1);
				}
				else
				{
					return 0;
				}

				v1 = ttv1;
				v2 = ttv2;
				v3 = ttv3;
				v4 = ttv4;
			}

			return 0;
			}
			ENDCG
		}
	}
}
