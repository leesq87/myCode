using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class csText : MonoBehaviour {

	GameObject obj;
	Text txt;

	void Start(){
		obj = GameObject.Find ("txtCenter");
		txt = obj.GetComponent<Text> ();

		ChangeText ();
	}

	void ChangeText(){
		txt.text = "홍길동";
	}



}
