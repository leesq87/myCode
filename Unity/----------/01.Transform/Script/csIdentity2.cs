using UnityEngine;
using System.Collections;

public class csIdentity2 : MonoBehaviour {

	public float rotSpeed = 120;

	// Update is called once per frame
	void Update () {


		float amtRot = rotSpeed * Time.deltaTime;
		float ang = Input.GetAxis ("Horizontal");
		transform.Rotate (Vector3.up * ang * amtRot);

		if (Input.GetButtonDown ("Fire1")) {
			transform.rotation = Quaternion.identity;
			//transform.localRotation = Quaternion.identity;
		}

	}
}
