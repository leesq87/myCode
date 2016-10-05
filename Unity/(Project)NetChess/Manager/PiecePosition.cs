using UnityEngine;
using System.Collections;

public class PiecePosition : MonoBehaviour {

    public spaceState state;
    public enum spaceState
    {
        normal,
        blackPiece,
        whitePiece,
        blackKing,
        whiteKing
    };

    public bool blackDead = false;
    public bool whiteDead = false;

    // Use this for initialization
    void Awake ()
	{
        stateUpdate();
    }
	
	// Update is called once per frame
	void Update ()
	{
	
	}

    public void stateUpdate()
    {
        if (transform.childCount > 0)
        {
            Transform child = transform.GetChild(0);
            if(child.tag == "BlackPiece")
            {
                state = spaceState.blackPiece;
            }
            else if (child.tag == "WhitePiece")
            {
                state = spaceState.whitePiece;
            }
            else if (child.tag == "BlackKing")
            {
                state = spaceState.blackKing;
            }
            else if (child.tag == "WhiteKing")
            {
                state = spaceState.whiteKing;
            }
        }
        else
        {
            state = spaceState.normal;
        }
    }

	public void ResetDeadZone()
	{
		blackDead = false;
		whiteDead = false;
	}

}
