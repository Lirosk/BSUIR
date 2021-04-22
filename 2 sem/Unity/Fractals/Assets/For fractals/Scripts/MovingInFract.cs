using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Text.RegularExpressions;
using UnityEngine;

public class MovingInFract : MonoBehaviour
{
	public Material mat;
	public Vector2 pos;
	public float scale = 3f;
	public float smooth = 0.3f;

	private Vector2 smoothPos;
	private float smoothScale;

	private float LogRegressSerp(float x)  //Logarithmic regression for Sierpinski  fractals
	{
		return 9.4514624177f - 1.4328380519f * (float)Math.Log(x);
	}

	private float LogRegressFBS(float x)  //Logarithmic regression for fractal by Squares
	{
		return 11.6665200498f - 1.4695802036f * (float)Math.Log(x);
	}

	private float LogRegressFBT(float x)//Logarithmic regression for fractal by Triangles
	{
		return 8.648433152526f - 1.435240568838f * (float)Math.Log(x);
	}

	private void UpdateShader()
	{
		smoothPos = Vector2.Lerp(smoothPos, pos, smooth);
		smoothScale = Mathf.Lerp(smoothScale, scale, smooth);		

		float aspect = (float)Screen.width / (float)Screen.height;

		float scaleX = scale;
		float scaleY = scale;

		if (aspect > 1f)
		{
			scaleY /= aspect;
		}
		else
		{
			scaleX *= aspect;
		}

		mat.SetVector("_Area", new Vector4(smoothPos.x, smoothPos.y, scaleX, scaleY));

		try
		{
			mat.SetFloat("_MaxIterSerp", LogRegressSerp((float)scale));
		}  
		catch
		{
			//yep, void
		}
		try
		{
			mat.SetFloat("_MaxIterFBS", LogRegressFBS((float)scale) + .9f);
		}
		catch
		{
			//yep, void
		}
		try
		{
			mat.SetFloat("_MaxIterFBT", LogRegressFBT((float)scale) + .9f);
		}
		catch
		{
			//yep, void
		}		
	}

	private void HandleInputs()
	{
		if (Input.GetKey(KeyCode.KeypadPlus))
		{
			scale /= 1.01f;
		}
		if (Input.GetKey(KeyCode.KeypadMinus))
		{
			scale /= .99f;
		}

		if (Input.GetKey(KeyCode.A))
		{
			pos.x -= .01f * scale;
		}
		if (Input.GetKey(KeyCode.D))
		{
			pos.x += .01f * scale;
		}

		if (Input.GetKey(KeyCode.W))
		{
			pos.y += .01f * scale;
		}
		if (Input.GetKey(KeyCode.S))
		{
			pos.y -= .01f * scale;
		}
	}

	// Update is called once per frame
	void FixedUpdate()
	{
		HandleInputs();
		UpdateShader();
	}
}



