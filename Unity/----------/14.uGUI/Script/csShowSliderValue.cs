using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class csShowSliderValue : MonoBehaviour {
	public void Updatelabel(float value){
		Text lbl = GetComponent<Text> ();
		if (lbl != null)
			lbl.text = Mathf.RoundToInt (value * 10) + "%";
	}



}
