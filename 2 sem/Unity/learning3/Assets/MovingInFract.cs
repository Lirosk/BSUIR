using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Runtime.ExceptionServices;
using System.Security.Cryptography.X509Certificates;
using UnityEngine;

public class MovingInFract : MonoBehaviour
{
    public Material mat;
    public Vector2 pos;
    public float scale = 3f;
    //public float angle = 0f;
    public float smooth = 0.3f;

    private Vector2 smoothPos;
    private float smoothScale;
    //private float smoothAngle;

    private void UpdateShader()
    {
        smoothPos = Vector2.Lerp(smoothPos, pos, smooth);
        smoothScale = Mathf.Lerp(smoothScale, scale, smooth);
        //smoothAngle = Mathf.Lerp(smoothAngle, angle, smooth);

        float aspect = (float)Screen.width / (float)Screen.height;

        float scaleX = scale;
        float scaleY = scale;

        if (aspect > 1f)
        {
            scaleX *= aspect;
        }
        else
        {
            scaleY /= aspect;
        }

        mat.SetVector("_Area", new Vector4(smoothPos.x, smoothPos.y, scaleX, scaleY));
        //mat.SetFloat("_Angle", smoothAngle);
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

        /*
        if (Input.GetKey(KeyCode.Q))
        {
            angle += .01f;
        }
        if (Input.GetKey(KeyCode.E))
        {
            angle -= .01f;
        }
        */

        //Vector2 dir = new Vector2(.01f * scale, 0);
        //float s = Mathf.Sin(angle);
        //float c = Mathf.Cos(angle);
        //dir = new Vector2(dir.x * c - dir.y * s, dir.x * s + dir.y * c)*.5f;

        if (Input.GetKey(KeyCode.A))
        {
            //pos -= dir;
            pos.x -= .01f * scale;
        }
        if (Input.GetKey(KeyCode.D))
        {
            //pos += dir;
            pos.x += .01f * scale;
        }

        //dir = new Vector2(-dir.y, dir.x);
        if (Input.GetKey(KeyCode.W))
        {
            //pos += dir;
            pos.y += .01f * scale;
        }
        if (Input.GetKey(KeyCode.S))
        {
            //pos -= dir;
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



