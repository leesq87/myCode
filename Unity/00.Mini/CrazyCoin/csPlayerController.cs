using UnityEngine;
using System.Collections;
using UnityEngine.Audio;

public class csPlayerController : MonoBehaviour {

	float walkSpeed = 3.0f;
	float gravity = 20.0f;
	float jumpSpeed = 8.0f;

	public AudioClip jumpSE;
	public AudioClip TouchSE;

	public Animation anim;

	private Vector3 velocity;
	private bool wasGrounded = false;


	void Start(){
				
		 GetComponent<Animation>() ["Walk"].speed = 2.0f;

	}

	void Update ()
	{

		CharacterController controller = GetComponent<CharacterController> ();

		if (controller.isGrounded) {
			if (!wasGrounded) {
								anim.Play ("Crouch");
//				GetComponent<Animation>().Play("Crouch");
				GetComponent<AudioSource>().PlayOneShot(TouchSE);
			}

			velocity =new Vector3 (Input.GetAxis ("Horizontal"), 0, Input.GetAxis ("Vertical"));
			velocity *= walkSpeed;
	
			if (Input.GetButtonDown ("Jump")) {
				velocity.y = jumpSpeed;
								anim.Play ("Jump");
				GetComponent<AudioSource> ().PlayOneShot (jumpSE);
			} else if (velocity.magnitude > 0.5) {
								anim.CrossFade ("Walk", 0.1f);
				transform.LookAt (transform.position + velocity);
			} else {
								anim.CrossFade ("Idle", 0.1f);
			}
		}

		wasGrounded = controller.isGrounded;

		velocity.y -= gravity * Time.deltaTime;

		controller.Move (velocity * Time.deltaTime);

	}
				
}
