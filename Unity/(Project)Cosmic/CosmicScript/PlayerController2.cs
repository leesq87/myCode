using UnityEngine;
using System.Collections;

public class PlayerController2 : MonoBehaviour
{

    public float movSpeed = 1;
    public float runSpeed = 2;
    public float rotSpeed = 2;
    public float animSpeed = 1.5f;
    public float gravity = 20f;
    bool running = true;

    private Vector3 movDir;
    public Animator anim;


    public Vector3 posi = new Vector3(0.6f, 6.5f, 23f);

    public Vector3 velocity;
    private Vector3 moveTo;


    void start()
    {
        anim = GetComponentInChildren<Animator>();

    }

    //void FixedUpdate()
    void Update()
    {
        if (Input.GetButtonUp("Fire1"))
        {
            moveTo = new Vector3(0, 0, 0);

            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                moveTo = new Vector3(hit.point.x, transform.position.y, hit.point.z);
            }
        }

        if (moveTo.magnitude == 0)
        {
            velocity = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            velocity *= runSpeed;

            if (velocity.magnitude > 0.5)
            {
                anim.SetBool("running", running);
                anim.SetFloat("speed", 1f);
                transform.LookAt(transform.position + velocity);
            }
            else {
                anim.SetBool("running", false);
            }
        }
        else {
            float distance = (moveTo - transform.position).magnitude;

            if (distance < 0.5)
            {
                moveTo = new Vector3(0, 0, 0);
            }

            int xto = 0;
            int zto = 0;

            if ((moveTo.x - transform.position.x) > 0)
                xto = 1;
            if ((moveTo.x - transform.position.x) < 0)
                xto = -1;
            if ((moveTo.z - transform.position.z) > 0)
                zto = 1;
            if ((moveTo.z - transform.position.z) < 0)
                zto = -1;

            velocity = new Vector3(xto, 0, zto);
            velocity *= runSpeed;

            if (velocity.magnitude > 0.5)
            {
                anim.SetBool("running", running);
                anim.SetFloat("speed", 1f);
                transform.LookAt(moveTo);
            }
            else {
                anim.SetBool("running", false);
            }
        }

        gameObject.transform.position = Vector3.MoveTowards(this.transform.position, moveTo, 1f);
        //velocity.y -= gravity * Time.deltaTime;
        //GetComponent<Rigidbody>().MovePosition(velocity * Time.deltaTime);
    }

    void FixedUpdate()
    {
        //transform.Translate(moveTo);

        //GetComponent<Rigidbody>().MovePosition(GetComponent<Rigidbody>().position + velocity * Time.deltaTime);
    }
    
}
