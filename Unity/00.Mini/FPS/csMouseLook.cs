using UnityEngine;
using System.Collections;

public class csMouseLook : MonoBehaviour {

	//public float sensitivity = 700.0f;
	public float sensitivity = 450.0f;
	public float rotationX;
	public float rotationY;

	csPlayerState playerHealth = null;

	void Start(){

		playerHealth = transform.parent.GetComponent<csPlayerState> ();
	}


	void Update(){

		if (playerHealth.isDead) {
			return;
		}

		float mouseMoveValueX = Input.GetAxis ("Mouse X");
		float mouseMoveValueY = Input.GetAxis ("Mouse Y");

		rotationY += mouseMoveValueX * sensitivity * Time.deltaTime;
		rotationX += mouseMoveValueY * sensitivity * Time.deltaTime;

		if (rotationX > 50.0f)
			rotationX = 50.0f;
		if (rotationX < -30.0f)
			rotationX = -30.0f;
/*
		if (rotationY > 180.0f)
			rotationY = 180.0f;
		if (rotationY < -180.0f)
			rotationY = -180.0f;
*/
		transform.eulerAngles = new Vector3 (-rotationX, rotationY, 0.0f);
	}


}
