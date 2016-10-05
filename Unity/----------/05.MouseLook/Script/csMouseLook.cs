using UnityEngine;
using System.Collections;

public class csMouseLook : MonoBehaviour {

	public float sensitivity = 500.0f;
	public float rotationX;
	public float rotationY;

	void Update(){

		//move mouse right,left
		float mouseMoveValueX = Input.GetAxis ("Mouse X");
		//move mouse up & down
		float mouseMoveValueY = Input.GetAxis ("Mouse Y");

		rotationX += mouseMoveValueX * sensitivity * Time.deltaTime;
		rotationY += mouseMoveValueY * sensitivity * Time.deltaTime;

		//move to front about mouse
		if (rotationY > 45.0f) {
			rotationY = 45.0f;
		}
		//move to back about mouse
		if (rotationY < -20.0f) {
			rotationY = -20.0f;
		}

		transform.eulerAngles = new Vector3 (-rotationY, rotationX, 0.0f);
	}


}
