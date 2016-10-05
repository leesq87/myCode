using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEditor;



public class csInput : MonoBehaviour {

	Text txt;
	InputField input1;
	InputField input2;
	InputField input3;

	void Start(){
		txt = GameObject.Find ("txtCenter").GetComponent<Text> ();
		input1 = GameObject.Find ("InputField1").GetComponent<InputField> ();
		input2 = GameObject.Find ("InputField2").GetComponent<InputField> ();
		input3 = GameObject.Find ("InputArea").GetComponent<InputField> ();

	}

	public void ChangeValue ()
	{

		if (txt.text.Length < 4) {
			if (EditorUtility.DisplayDialog ("알림", "입력은 4자 이상 해주시기 바랍니다.", "확인")) {
				input1.Select ();
				//input1.ActivateInputField ();
			}else {
				txt.text = input1.text;
			}
		} 

		Debug.Log ("IputField1 : " + input1.text);
		Debug.Log ("inputField2 : " + input2.text);
		Debug.Log ("InputArea : " + input3.text);
	}



}
