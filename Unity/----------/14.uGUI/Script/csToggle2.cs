using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class csToggle2 : MonoBehaviour {

	Text txt;
	Toggle tgChange;

	void Start(){
		txt = GameObject.Find ("txtCenter").GetComponent<Text> ();
		tgChange = GameObject.Find ("tgChangeText1").GetComponent<Toggle> ();
	}

	public void ChangeText(){
		if (tgChange.isOn) {
			txt.text = "Hello World";
		} else {
			txt.text = "홍길동";
		}
	}


}
