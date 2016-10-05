using UnityEngine;
using System.Collections;

public class csIdentity : MonoBehaviour {

	public float rotSpeed = 120;

	// Update is called once per frame
	void Update () {
	

		float amtRot = rotSpeed * Time.deltaTime;
		float ang = Input.GetAxis ("Horizontal");
		transform.Rotate (Vector3.up * ang * amtRot);

		if (Input.GetButtonDown ("Fire1")) {
			transform.localRotation = Quaternion.identity;
		}

	}
}
