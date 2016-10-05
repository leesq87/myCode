using UnityEngine;
using System.Collections;

public class csJump2 : MonoBehaviour {

	Vector3 velocity = new Vector3(0,400,0);


	void FixedUpdate(){
		if(Input.GetButtonDown("Jump")){
			GetComponent<Rigidbody> ().AddForce (velocity);
		}
	}

}
