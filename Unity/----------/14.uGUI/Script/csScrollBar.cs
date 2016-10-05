using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class csScrollBar : MonoBehaviour {

	Text lbl;

	void Start(){
		lbl = GetComponent<Text> ();
	}

	public void UpdateLabel(float value){
		if(lbl!=null){
			lbl.text = string.Format ("{0:0.00}", value);
		}
	}



}
