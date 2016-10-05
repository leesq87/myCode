using UnityEngine;
using System.Collections;

public class csCollisionCheck : MonoBehaviour {

	void OnCollisionEnter(Collision collision){
		Debug.Log ("OnCollisionEnter");
	}

	void OnTriggerEnter(Collider other){
		Debug.Log ("OnTriggerEnter");

		GetComponent<Rigidbody> ().isKinematic = false;
		GetComponent<Rigidbody> ().AddForce (new Vector3 (0, 200, -200));
	}
}
