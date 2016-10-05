using UnityEngine;
using System.Collections;

public class csGameManager : MonoBehaviour {

	GameObject obj = null;

	void Start(){
		obj = GameObject.Find ("Cube");
	}

	void OnGUI(){
		if (GUI.Button (new Rect (30, 50, 180, 30), "Function Call(Public)")){
			//call method in some Object
			csRotateCube script = obj.GetComponent<csRotateCube>();
			script.Rotate1();
		}

		if(GUI.Button(new Rect(30,100,180,30),"FunctionCall (Private)")){
			//send message
			obj.SendMessage ("Rotate2", SendMessageOptions.DontRequireReceiver);
		}

		if(GUI.Button (new Rect(30,150,180,30),"Static")){
			// attich static func or var
			Debug.Log("Call Variable : "+csRotateCube.numX);
			Debug.Log ("Call Function : " + csRotateCube.AddTwoNum (3, 5));
		}
	}
			




}
