using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;


public class csHuman : MonoBehaviour {

    public GUISkin skin;

    GameObject manager;

    int speedForward = 12;
    int speedSide = 6;
    int jumpPower = 250;

    bool canJump = true;
    bool canTurn = false;
    bool canLeft = true;
    bool canRight = true;
    bool isGround = true;
    bool isDead = false;

    float dirX = 0;
    float score = 0;

    Vector3 touchStart;

    void Start()
    {
        Screen.orientation = ScreenOrientation.Portrait;
        Screen.sleepTimeout = SleepTimeout.NeverSleep;

        manager = GameObject.Find("BridgeManager");

    }

    void Update()
    {
        if (isDead)
            return;
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }

        CheckMove();
        MoveHuman();

        score += Time.deltaTime * 1000;
    }

    //이동가능한 상태인지 조사
    void CheckMove()
    {
        RaycastHit hit;

        //down - 주인공이 다리위에 있는가?
        isGround = true;
        if (Physics.Raycast(transform.position, Vector3.down, out hit, 2f))
        {
            if (hit.transform.tag == "BRIDGE")
            {
                isGround = true;
            }
        }


        //left - 왼쪽이동가능?
        canLeft = true;
        if (Physics.Raycast(transform.position, -transform.right, out hit, 0.7f))
        {
            if (hit.transform.tag == "GUARD")
            {
                canLeft = false;
            }
        }

        //right - 오른쪽이동가능?
        canRight = true;
        if (Physics.Raycast(transform.position, transform.right, out hit, 0.7f))
        {
            if (hit.transform.tag == "GUARD")
            {
                canRight = false;
            }
        }
    }

    //주인공이동
    void MoveHuman()
    {
        dirX = 0;

        //mobile
        if (Application.platform == RuntimePlatform.Android ||
            Application.platform == RuntimePlatform.IPhonePlayer)
        {
            CheckMobile();
        }
        else
        {
            CheckKeyboard();
        }

        Vector3 moveDir = new Vector3(dirX * speedSide, 0, speedForward);
        transform.Translate(moveDir * Time.smoothDeltaTime);
    }


    //모바일기기 조사
    void CheckMobile()
    {

        
    }


    //키보드 조사
    void CheckKeyboard()
    {
        float key = Input.GetAxis("Horizontal");
        if (key < 0 && canLeft && isGround)
            dirX = -1;
        if (key > 0 && canRight && isGround)
            dirX = 1;

        //jump
        if (isGround && canJump && Input.GetKeyDown(KeyCode.Space))
        {
            StartCoroutine("JumpHuman");
        }

        //Turn
        if (canTurn)
        {
            if (Input.GetKeyDown(KeyCode.Q))
                RotateHuman("LEFT");
            if (Input.GetKeyDown(KeyCode.E))
                RotateHuman("RIGHT");
        }
    }

    IEnumerator JumpHuman()
    {
        canJump = false;
        GetComponent<Rigidbody>().AddForce(Vector3.up * jumpPower);
        GetComponent<Animation>().Play("jump_pose");

        yield return new WaitForSeconds(1);

        GetComponent<Animation>().Play("run");
        canJump = true;
    }

    //Rotate
    void RotateHuman(string sDir)
    {
        canTurn = false;

        Vector3 rot = transform.eulerAngles;

        switch (sDir)
        {
            case "LEFT":
                rot.y -= 90;
                break;
            case "RIGHT":
                rot.y += 90;
                break;
        }

        transform.eulerAngles = rot;

        manager.SendMessage("makeBridge", sDir, SendMessageOptions.DontRequireReceiver);
    }

    //DeadZone
    void OnCollisionEnter(Collision coll)
    {
        if (coll.transform.tag == "DEAD")
        {
            isDead = true;
            GetComponent<Animation>().Play("idle");
        }
    }


    void OnTriggerEnter(Collider coll)
    {
        switch (coll.transform.tag)
        {
            case "TURN":
                canTurn = true;
                break;
            case "COIN":
                score += 1000;
                Destroy(coll.gameObject);
                break;
        }
    }

    void OnTriggerExit(Collider coll)
    {
        if(coll.tag == "TURN")
        {
            canTurn = false;

        }
    }


    void OnGUI()
    {
        GUI.skin = skin;

        string str = "<size=20><color=#ffffff>Score : ##</Color></size>";
        GUI.Label(new Rect(10, 10, 300, 80), str.Replace("##", "" + (int)score));

        if (!isDead)
            return;
        GetComponent<Animation>().Play("idle");
        int w = Screen.width / 2;
        int h = Screen.height / 2;

        if (GUI.Button(new Rect(w - 60, h - 50, 120, 50), "Play Game"))
        {
            SceneManager.LoadScene("Game");
        }

        if(GUI.Button(new Rect(w-60,h+50,120,50),"Quit Game"))
        {
            Application.Quit();
        }
    }



}
