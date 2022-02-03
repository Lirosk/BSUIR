using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DropdownChange : MonoBehaviour
{
	public Dropdown dropdown;
	public Material mat;
	public MovingInFract script;

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

	public GameObject AlgNeed;
	public GameObject AlgVar;
	public GameObject GeometryVar;

	public GameObject Vertex4;

	public void Dropdown_IndexChange()
	{
			string shader = dropdown.options[dropdown.value].text;
			mat.shader = Shader.Find("Fractals/" + shader);
			
			switch (shader)
			{
				case("Mandelbrot"):
				{
					SetMandelbrot();
					SetMandelbrotInput();
					break;
				}
				case("Julia"):
				{
					SetJulia();
					SetJuliaInput();
					break;
				}
				case("Newtone fractal"):
				{
					SetNewtonefractal();	
					SetNewtonefractalInput();			
					break;
				}
				case("Random fractal"):
				{
					SetRandomfractal();		
					SetRandomfractalInput();		
					break;
				}
				case("Sierpinski triangle"):
				{
					SetSierpinskitriangle();	
					SetSierpinskitriangleInput();				
					break;
				}
				case("Sierpinski square"):
				{
					SetSierpinskisquare();
					SetSierpinskisquareInput();				
					break;
				}
				case("T-square"):
				{
					SetTsquare();		
					SetTsquareInput();		
					break;
				}
				case("Christmas tree"):
				{
					SetChristmastree();		
					SetChristmastreeInput();		
					break;
				}
			}		
		
	}

    // Start is called before the first frame update
    void Start()
    {
    	SetMandelbrot();
    	SetMandelbrotInput();
    }

    private void SetMandelbrot()
    {
    	mat.shader = Shader.Find("Fractals/Mandelbrot");
        mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
		mat.SetFloat("_MaxIter", 256f);
		mat.SetFloat("_Radius", 20f);
		mat.SetFloat("_Color", .5f);
		mat.SetFloat("_Power", 2f);
		mat.SetFloat("_Speed", .01f);
		mat.SetFloat("_Repeat", 1f);	
		script.scale = 5f;	
		script.pos = new Vector2(0f, 0f);		
    }

    private void SetMandelbrotInput()
    {
		AlgNeed.SetActive(true);
    	AlgVar.SetActive(false);
    	GeometryVar.SetActive(false);

    	InputFieldIter.text = "256";
		InputFieldColor.text = "0,5"; 
		InputFieldColorRepeat.text = "1";
		InputFieldColorSpeed.text = "0,01";
		InputFieldRadius.text = "20";
		InputFieldPower.text = "2";
    }

    private void SetJulia()
    {
		mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
		mat.SetFloat("_MaxIter", 256f);
		mat.SetFloat("_Radius", 20f);
		mat.SetFloat("_Color", .5f);
		mat.SetFloat("_Power", 2f);
		mat.SetFloat("_Speed", .01f);
		mat.SetFloat("_Repeat", 1f);
		mat.SetFloat("_R", 0f);
		mat.SetFloat("_I", .8f);
		mat.SetFloat("_ShapeSpeed", .5f);
		mat.SetFloat("_CircleRadius", .5f);
		script.scale = 5f;
		script.pos = new Vector2(0f, 0f);		
    }

    private void SetJuliaInput()
    {
		AlgNeed.SetActive(true);
    	AlgVar.SetActive(true);
    	GeometryVar.SetActive(false);

    	InputFieldIter.text = "256";
		InputFieldColor.text = "0,5"; 
		InputFieldColorRepeat.text = "1";
		InputFieldColorSpeed.text = "0,01";
		InputFieldRadius.text = "20";
		InputFieldPower.text = "2";

		InputFieldVariableRadius.text = "0,5";
		InputFieldVariableImaginaryPart.text = "0,8";
		InputFieldVariableRealPart.text = "0";
		InputFieldShapeSpeed.text = "0,5";
    }

    private void SetNewtonefractal()
    {
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
		mat.SetFloat("_MaxIter", 256f);
		mat.SetFloat("_Color", .7f);
		mat.SetFloat("_Speed", .01f);
		mat.SetFloat("_Repeat", 1f);
		mat.SetFloat("_Radius", .0001f);
		mat.SetFloat("_Power", 3f);
		mat.SetFloat("_R", 1f);
		mat.SetFloat("_I", 0f);
		mat.SetFloat("_ShapeSpeed", .5f);
		mat.SetFloat("_CircleRadius", .5f);
		script.scale = 5f;
		script.pos = new Vector2(0f, 0f);
    }

    private void SetNewtonefractalInput()
    {
		AlgNeed.SetActive(true);
    	AlgVar.SetActive(true);
    	GeometryVar.SetActive(false);

    	InputFieldIter.text = "256";
		InputFieldColor.text = "0,7"; 
		InputFieldColorRepeat.text = "1";
		InputFieldColorSpeed.text = "0,01";
		InputFieldRadius.text = "0,0001";
		InputFieldPower.text = "3";

		InputFieldVariableRadius.text = "0,5";
		InputFieldVariableImaginaryPart.text = "0";
		InputFieldVariableRealPart.text = "1";
		InputFieldShapeSpeed.text = "0,5";
    }

    private void SetRandomfractal()
    {
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
		mat.SetFloat("_MaxIter", 256f);
		mat.SetFloat("_Color",.6f);
		mat.SetFloat("_Repeat", 1f);
		mat.SetFloat("_Speed", .0f);		
		mat.SetFloat("_Radius", .2f);
		mat.SetFloat("_Power", 2f);
		mat.SetFloat("_R", 3.79f);
		mat.SetFloat("_I", 0.87f);
		mat.SetFloat("_ShapeSpeed", .5f);
		mat.SetFloat("_CircleRadius", .5f);
		script.pos = new Vector2(-0.9287205f, -1.076767f);
		script.scale = 21f;
    }

    private void SetRandomfractalInput()
    {
		AlgNeed.SetActive(true);
    	AlgVar.SetActive(true);
    	GeometryVar.SetActive(false);  

    	InputFieldIter.text = "256";
		InputFieldColor.text = "0,6"; 
		InputFieldColorRepeat.text = "1";
		InputFieldColorSpeed.text = "0";
		InputFieldRadius.text = "0,2";
		InputFieldPower.text = "2";

		InputFieldVariableRadius.text = "0,5";
		InputFieldVariableImaginaryPart.text = "0,87";
		InputFieldVariableRealPart.text = "3.79";
		InputFieldShapeSpeed.text = "0,5";
	}

    private void SetSierpinskitriangle()
    {    	
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
    	script.pos = new Vector2(0f, 4.960936f);
    	script.scale = 19f;
    	mat.SetVector("_V1", new Vector4(0f, 10f, 0f, 0f));
    	mat.SetVector("_V2", new Vector4(5.77350269189625f, 0f, 0f, 0f));
    	mat.SetVector("_V3", new Vector4(-5.77350269189625f, 0f, 0f, 0f));
    }

    private void SetSierpinskitriangleInput()
    {
		AlgNeed.SetActive(false);
    	AlgVar.SetActive(false);
    	GeometryVar.SetActive(true);
    	Vertex4.SetActive(false);

    	InputFieldVertex1x.text = "0";
    	InputFieldVertex1y.text = "10";

    	InputFieldVertex2x.text = "5.77350269189625";
    	InputFieldVertex2y.text = "0";

    	InputFieldVertex3x.text = "-5.77350269189625";
    	InputFieldVertex3y.text = "0";
    }

    private void SetSierpinskisquare()
    {
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
    	script.pos = new Vector2(0f, 0f);
    	script.scale = 37f;
    	mat.SetVector("_V1", new Vector4(-10f, 10f, 0f, 0f));
    	mat.SetVector("_V2", new Vector4(10f, 10f, 0f, 0f));
    	mat.SetVector("_V3", new Vector4(10f, -10f, 0f, 0f));
    	mat.SetVector("_V4", new Vector4(-10f, -10f, 0f, 0f));
    }

    private void SetSierpinskisquareInput()
    {
		AlgNeed.SetActive(false);
    	AlgVar.SetActive(false);
    	GeometryVar.SetActive(true);
    	Vertex4.SetActive(true);

    	InputFieldVertex1x.text = "-10";
    	InputFieldVertex1y.text = "10";

    	InputFieldVertex2x.text = "10";
    	InputFieldVertex2y.text = "10";

    	InputFieldVertex3x.text = "10";
    	InputFieldVertex3y.text = "-10";

    	InputFieldVertex4x.text = "-10";
    	InputFieldVertex4y.text = "-10";
    }

    private void SetTsquare()
    {
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
    	script.pos = new Vector2(0f, 0f);
    	script.scale = 38f;
    	mat.SetVector("_V1", new Vector4(-10f, 10f, 0f, 0f));
    	mat.SetVector("_V2", new Vector4(10f, 10f, 0f, 0f));
    	mat.SetVector("_V3", new Vector4(10f, -10f, 0f, 0f));
    	mat.SetVector("_V4", new Vector4(-10f, -10f, 0f, 0f));
    }

    private void SetTsquareInput()
    {
		AlgNeed.SetActive(false);
    	AlgVar.SetActive(false);
    	GeometryVar.SetActive(true);
    	Vertex4.SetActive(true);

    	InputFieldVertex1x.text = "-10";
    	InputFieldVertex1y.text = "10";

    	InputFieldVertex2x.text = "10";
    	InputFieldVertex2y.text = "10";

    	InputFieldVertex3x.text = "10";
    	InputFieldVertex3y.text = "-10";

    	InputFieldVertex4x.text = "-10";
    	InputFieldVertex4y.text = "-10";
    }

    private void SetChristmastree()
    {
    	mat.SetVector("_Area", new Vector4(0f, 0f, 4f, 4f));
    	script.pos = new Vector2(0f, 4.960936f);
    	script.scale = 18f;
    	mat.SetVector("_V1", new Vector4(0f, 10f, 0f, 0f));
    	mat.SetVector("_V2", new Vector4(5.77350269189625f, 0f, 0f, 0f));
    	mat.SetVector("_V3", new Vector4(-5.77350269189625f, 0f, 0f, 0f));
    }

    private void SetChristmastreeInput()
    {
		AlgNeed.SetActive(false);
    	AlgVar.SetActive(false);
    	GeometryVar.SetActive(true);
    	Vertex4.SetActive(false);

    	InputFieldVertex1x.text = "0";
    	InputFieldVertex1y.text = "10";

    	InputFieldVertex2x.text = "5.77350269189625";
    	InputFieldVertex2y.text = "0";

    	InputFieldVertex3x.text = "-5.77350269189625";
    	InputFieldVertex3y.text = "0";
    }
}
