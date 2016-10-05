using UnityEngine;
using System.Collections;

public class csCharacterMove : MonoBehaviour {

	public Transform cameraTransform;

	public float moveSpeed = 10.0f;
	public float jumpSpeed = 10.0f;
	public float gravity = -20.0f;

	CharacterController characterController = null;
	float yVelocity = 0.0f;

	csPlayerState playerHealth = null;


	void Start(){
		characterController = GetComponent<CharacterController> ();
		playerHealth = GetComponent<csPlayerState> ();

	}

	void Update(){

		if (playerHealth.isDead) {
			return;
		}


		float y = transform.position.y;
		if (y < 0) {
			gameObject.transform.position = new Vector3 (0f, 40f, 0f);
		}

		float x = Input.GetAxis ("Horizontal");
		float z = Input.GetAxis ("Vertical");

		Vector3 moveDirection = new Vector3 (x, 0, z);
		moveDirection = cameraTransform.TransformDirection (moveDirection);

		moveDirection *= moveSpeed;

		if (characterController.isGrounded) {
			yVelocity = 0.0f;
			if (Input.GetButtonDown ("Jump")) {
				yVelocity = jumpSpeed;
			}
		}

		yVelocity += (gravity * Time.deltaTime);
		moveDirection.y = yVelocity;

		characterController.Move (moveDirection * Time.deltaTime);
	}
}
