using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class csToggle1 : MonoBehaviour {

	Text txt;
	Toggle tgChangeText;

	void Start(){
		txt = GameObject.Find ("txtCenter").GetComponent<Text> ();
		tgChangeText = GameObject.Find ("tgChangeText").GetComponent<Toggle> ();

	}

	public void ChangeText(){
		if (tgChangeText.isOn) {
			txt.text = "Hello World!";
		} else {
			txt.text = "홍길동";
		}
	}



}
