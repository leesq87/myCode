using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class PlayerController : MonoBehaviour {

	public float movSpeed = 1;
	public float runSpeed = 2;
    public float rotSpeed = 2;
	public float animSpeed = 1.5f;
	bool running = true;

	private Vector3 movDir;
	public Animator anim;


    public Vector3 posi = new Vector3(0.6f, 6.5f, 23f);

    private Vector3 moveTo;


    void start()
	{
		anim = GetComponentInChildren<Animator>();
        //posi = new Vector3(0.6f, 6.4f, 23f);

        Debug.Log(posi);
	}
	void Update () 
	{
        if (gameObject.scene.name != "Defense")
        {


            //posi = this.gameObject.transform.position;

            float speed = Input.GetAxis("Vertical");
            //Debug.Log(speed);
            float turn = Input.GetAxis("Horizontal");

            // GetAxis -> -1~1

            //running = Input.GetKey (KeyCode.LeftShift);
            anim.SetBool("running", running);

            movDir = new Vector3(0, 0, Input.GetAxisRaw("Vertical")).normalized;
            transform.Rotate(new Vector3(0, turn * rotSpeed, 0));
            //		transform.rotation = new Quaternion (turn, transform.rotation.y, transform.rotation.z, transform.rotation.w);
            //		float speed = Input.GetAxis("Vertical");
            anim.SetFloat("speed", speed);
        }
    }

	void FixedUpdate()
	{
        //if (!running)
        //    GetComponent<Rigidbody>().MovePosition(GetComponent<Rigidbody>().position + transform.TransformDirection(movDir * movSpeed * Time.deltaTime));
        //else
        GetComponent<Rigidbody>().MovePosition(GetComponent<Rigidbody>().position + transform.TransformDirection(movDir * runSpeed * Time.deltaTime));
        //GetComponent<Rigidbody>().MovePosition(posi);


    }

    public void getPointToMove(Vector3 position)
    {
        Debug.Log(position);
        posi = position;
    }
}
