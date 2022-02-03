using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Linq;

public class Params : MonoBehaviour
{
	public Material mat;
	public InputField InputFieldIter;
	public InputField InputFieldColor;
	public InputField InputFieldColorRepeat;
	public InputField InputFieldColorSpeed;
	public InputField InputFieldShapeSpeed;
	public InputField InputFieldRadius;
	public InputField InputFieldVariableRadius;	
	public InputField InputFieldVariableRealPart;
	public InputField InputFieldVariableImaginaryPart; 	
	public InputField InputFieldPower;

	public InputField InputFieldVertex1x;
	public InputField InputFieldVertex1y;
	public InputField InputFieldVertex2x;
	public InputField InputFieldVertex2y;
	public InputField InputFieldVertex3x;
	public InputField InputFieldVertex3y;
	public InputField InputFieldVertex4x;
	public InputField InputFieldVertex4y;

    // Update is called once per frame
    void Update()
    {
    	ReadIter();
        ReadRadius();
        ReadColor();
        ReadColorSpeed();
        ReadColorRepeat();
        ReadShapeSpeed();
        ReadVariableRadius();
        ReadVariableRealPart();
        ReadVariableImaginaryPart();
        ReadPower();

        ReadVertex1();
        ReadVertex2();
        ReadVertex3();
        ReadVertex4();
	}

	private void ReadIter()
    {
        try
        {
            float iter;

            string input = InputFieldIter.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out iter))
            {
                mat.SetFloat("_MaxIter", iter);
            }
        }
        catch
        {
            Debug.Log("Failing read _MaxIter");
        }
    }

    private void ReadColor()
    {
    	try
        {
            float color;

            string input = InputFieldColor.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out color))
            {
                mat.SetFloat("_Color", color);
            }
        }
        catch
        {
            Debug.Log("Failing read _Color");
        }
    }

    private void ReadRadius()
    {
        try
        {
            float Radius;

            string input = InputFieldRadius.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out Radius))
            {
                mat.SetFloat("_Radius", Radius);
            }
        }
        catch
        {
            Debug.Log("Failing read radius");
        }
    }

    private void ReadColorSpeed()
    {
        try
        {
            float ColorSpeed;

            string input = InputFieldColorSpeed.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out ColorSpeed))
            {
                mat.SetFloat("_Speed", ColorSpeed);
            }
        }
        catch
        {
            Debug.Log("Failing read color speed");
        }
    }

    private void ReadColorRepeat()
    {
        try
        {
            float ColorRepeat;

            string input = InputFieldColorRepeat.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out ColorRepeat))
            {
                mat.SetFloat("_Repeat", ColorRepeat);
            }
        }
        catch
        {
            Debug.Log("Failing read color repeat");
        }
    }

    private void ReadShapeSpeed()
    {        
        try
        {
            float ShapeSpeed;

            string input = InputFieldShapeSpeed.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out ShapeSpeed))
            {
                mat.SetFloat("_ShapeSpeed", ShapeSpeed);
            }
        }
        catch
        {
            Debug.Log("Failing read shape speed");
        }
    }

    private void ReadVariableRadius()
    {
        try
        {
            float VariableRadius;

            string input = InputFieldVariableRadius.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out VariableRadius))
            {
                mat.SetFloat("_CircleRadius", VariableRadius);
            }
        }
        catch
        {
            Debug.Log("Failing read variable radius");
        }
    }

    private void ReadVariableRealPart()
    {
        try
        {
            float VariableRealPart;

            string input = InputFieldVariableRealPart.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out VariableRealPart))
            {
                mat.SetFloat("_R", VariableRealPart);
            }
        }
        catch
        {
            Debug.Log("Failing read variable real part");
        }
    }

    private void ReadVariableImaginaryPart()
    {
        try
        {
            float VariableImaginaryPart;

            string input = InputFieldVariableImaginaryPart.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out VariableImaginaryPart))
            {
                mat.SetFloat("_I", VariableImaginaryPart);
            }
        }
        catch
        {
            Debug.Log("Failing read variable imaginary part");
        }
    }

    private void ReadPower()
    {
    	try
        {
            float Power;

			string input = InputFieldPower.text;

            int i = input.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input.ToCharArray();
            	buf[i] = ',';
            	input = new string(buf);
            }

            if (float.TryParse(input, out Power))
            {
                mat.SetFloat("_Power", Power);
            }
        }
        catch
        {
            Debug.Log("Failing read _Power");
        }
    }

    private void ReadVertex1()
    {
    	try
    	{
			float v1x;
			float v1y;

			string input1 = InputFieldVertex1x.text;

            int i = input1.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input1.ToCharArray();
            	buf[i] = ',';
            	input1 = new string(buf);
            }

            string input2 = InputFieldVertex1y.text;

            i = input2.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input2.ToCharArray();
            	buf[i] = ',';
            	input2 = new string(buf);
            }

			if (float.TryParse(input1, out v1x) && float.TryParse(input2, out v1y))
			{
				mat.SetVector("_V1",new Vector4(v1x, v1y, 0f, 0f));
			}
    	}
    	catch
    	{
    		Debug.Log("Failing read _V1");
    	}
    }

    private void ReadVertex2()
    {
    	try
    	{
			float v2x;
			float v2y;

			string input1 = InputFieldVertex2x.text;

            int i = input1.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input1.ToCharArray();
            	buf[i] = ',';
            	input1 = new string(buf);
            }

            string input2 = InputFieldVertex2y.text;

            i = input2.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input2.ToCharArray();
            	buf[i] = ',';
            	input2 = new string(buf);
            }

			if (float.TryParse(input1, out v2x) && float.TryParse(input2, out v2y))
			{
				mat.SetVector("_V2",new Vector4(v2x, v2y, 0f, 0f));
			}
    	}
    	catch
    	{
    		Debug.Log("Failing read _V2");
    	}
    }


    private void ReadVertex3()
    {
    	try
    	{
			float v3x;
			float v3y;

			string input1 = InputFieldVertex3x.text;

            int i = input1.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input1.ToCharArray();
            	buf[i] = ',';
            	input1 = new string(buf);
            }

            string input2 = InputFieldVertex3y.text;

            i = input2.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input2.ToCharArray();
            	buf[i] = ',';
            	input2 = new string(buf);
            }

			if (float.TryParse(input1, out v3x) && float.TryParse(input2, out v3y))
			{
				mat.SetVector("_V3",new Vector4(v3x, v3y, 0f, 0f));
			}
    	}
    	catch
    	{
    		Debug.Log("Failing read _V3");
    	}
    }

    private void ReadVertex4()
    {
    	try
    	{
			float v4x;
			float v4y;

			string input1 = InputFieldVertex4x.text;

            int i = input1.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input1.ToCharArray();
            	buf[i] = ',';
            	input1 = new string(buf);
            }

            string input2 = InputFieldVertex4y.text;

            i = input2.IndexOf('.');
            if (i != -1)
            {
            	char[] buf = input2.ToCharArray();
            	buf[i] = ',';
            	input2 = new string(buf);
            }

			if (float.TryParse(input1, out v4x) && float.TryParse(input2, out v4y))
			{
				mat.SetVector("_V4",new Vector4(v4x, v4y, 0f, 0f));
			}
    	}
    	catch
    	{
    		Debug.Log("Failing read _V4");
    	}
    }
}
