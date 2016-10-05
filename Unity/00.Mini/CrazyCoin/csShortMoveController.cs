using UnityEngine;
using System.Collections;

public class csShortMoveController : MonoBehaviour {

	float velocity = 8.0f;
	float moveDelay = 1.0f;
	float sustainTime = 3.0f;

	IEnumerator Start(){
		yield return new WaitForSeconds (moveDelay);

		GameObject player = GameObject.FindWithTag ("Player");

		if (player != null) {
			Vector3 direction = (player.transform.position - transform.position).normalized;

			GetComponent<Rigidbody> ().AddForce (direction * velocity, ForceMode.VelocityChange);
		}

		yield return new WaitForSeconds (sustainTime);


		Destroy (gameObject);
	}




}
