using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class EnergyText : MonoBehaviour {

    GameObject first;
	void Start () {
        first = this.gameObject;
        this.gameObject.GetComponent<Text>().CrossFadeAlpha(-1, 3.0f, false);
	}
	
	// Update is called once per frame
	void Update () {
	}

    public void setText(string s)
    {
        //this.transform = first;



    }
}
