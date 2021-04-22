using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeMenu : MonoBehaviour
{
    public GameObject Menu;

    // Start is called before the first frame update
    void Start()
    {
        Menu.SetActive(false);
        Cursor.visible = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
 			if (Menu.activeInHierarchy) //activeSelf or activeInHierarchy
 			{
 				Menu.SetActive(false);
                Cursor.visible = false;
 			}
 			else
 			{
 				Menu.SetActive(true);
                Cursor.visible = true;
 			}
        }
    }
}
