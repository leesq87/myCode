using UnityEngine;
using System.Collections;

public class csThrow2 : MonoBehaviour {

	// if you wnat to  apply a force over several frames
	// you should apply it inside FixedUpdate instead of Update


	void FixedUpdate(){
		if (Input.GetButtonDown ("Fire1")) {
			GetComponent<Rigidbody> ().velocity = new Vector3 (7, 7, 0);
		}
	}
}
