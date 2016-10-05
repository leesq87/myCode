using UnityEngine;
using System.Collections;

public class csLegacy1 : MonoBehaviour {

	bool bFast = false;

	public void doWalk(){
		StartCoroutine ("coWalk");
	}

	IEnumerator coWalk(){
		GetComponent<Animation> ().Play ("walk");
		yield return new WaitForSeconds (0.4f);
		GetComponent<Animation> ().Play ("iddle");

	}

	public void doJumpPose(){
		StartCoroutine ("coJumpPose");
	}

	IEnumerator coJumpPose(){

		//GetComponent<Animation> ().Play ("attack_leap");
		GetComponent<Animation> ().CrossFade ("attack_leap", 0.2f);
		yield return new WaitForSeconds (0.46f);

		//GetComponent<Animation> ().Play ("iddle");
		GetComponent<Animation> ().CrossFade ("iddle", 0.2f);

	}

	public void doWalkFast(){
		if(bFast){
			bFast = false;

			GetComponent<Animation>().Stop();
			GetComponent<Animation> () ["walk"].speed = 1.0f;
			GetComponent<Animation>()["walk"].wrapMode = WrapMode.Once;

			StartCoroutine ("coWalk");
		} else{
			bFast = true;

			GetComponent<Animation> ().Stop ();
			GetComponent<Animation>()["walk"].speed = 2.0f;
			GetComponent<Animation>()["walk"].wrapMode = WrapMode.Loop;
			GetComponent<Animation> ().Play ("walk");
		}
	}



}
