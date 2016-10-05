using UnityEngine;
using System.Collections;

public class csThrow1 : MonoBehaviour {

	float  power = 800;
	Vector3 velocity = new Vector3(0.5f,0.5f,0.0f);

	// if you wnat to  apply a force over several frames
	// you should apply it inside FixedUpdate instead of Update


	void FixedUpdate(){
		if (Input.GetButtonDown ("Fire1")) {
			velocity = velocity * power;

			GetComponent<Rigidbody> ().AddForce (velocity);
		}
	}
}
