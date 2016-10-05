using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class csSlider : MonoBehaviour {

	Text txt;
	Slider slider1;
	Slider slider2;
	int fontSize;

	void Start(){
		txt = GameObject.Find ("txtCenter").GetComponent<Text> ();

		slider1 = GameObject.Find ("Slider1").GetComponent<Slider> ();
		slider2 = GameObject.Find ("Slider2").GetComponent<Slider> ();

		fontSize = txt.fontSize;

	}

	public void ChangeSliderValue(){
		float val = slider2.value;
		Debug.Log("Slider2.value : "+val);

		slider1.value = val;
		txt.fontSize = fontSize + (int)val;
	}




}
