using UnityEngine;
using System.Collections;

public class csCoroutine1 : MonoBehaviour {

	void Update(){
		if (Input.GetButtonDown ("Fire1")) {
			StartCoroutine ("Exam1");
		}
	}

	IEnumerator Exam1(){

		//run when end of this rendderring
		yield return new WaitForEndOfFrame ();

		//run func or code
		FirstCall ();

		//after run when end of time
		yield return new WaitForSeconds (2.0f);

		//run
		SecondCall ();

	}

	void FirstCall(){
		Debug.Log ("First");
	}

	void SecondCall(){
		Debug.Log ("Second");
	}





}
