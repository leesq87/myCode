using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using System.Collections.Generic;


public class newDragPlanetList : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{
    float deltaX;
    static bool moving = false;
    csPlanetPanalSet script;

    void Start()
    {
        deltaX = 0;
        script = GameObject.Find("Manager/UIManager").GetComponent<csPlanetPanalSet>();
    }

    public void OnBeginDrag(PointerEventData eventData)
    {
        Debug.Log("OnBeginDrag");
        GameObject.Find("Manager").GetComponent<ManagePlanetRay>().enabled = false;  //버그피킹

        SoundManager.Instance().PlaySfx(SoundManager.Instance().dragPlanet);
    }

    public void OnDrag(PointerEventData eventData)
    {
        Debug.Log("OnDrag");
        deltaX = eventData.delta.y;

        if (!moving)
        {
            Debug.Log("if moving = false : active");
            StartCoroutine(dragFlase());

            if (deltaX > 0)
            {
                Debug.Log("deltaX > 0");

                MovePlanet.Instance.insertDrag();
                MovePlanet.Instance.moveUp();
            }
            else if (deltaX < 0)
            {
                Debug.Log("deltaX < 0");

                MovePlanet.Instance.insertDrag();
                MovePlanet.Instance.moveDown();
            }
        }
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        GameObject.Find("Manager").GetComponent<ManagePlanetRay>().enabled = true;
    }

    IEnumerator dragFlase()
    {
        moving = true;
        Debug.Log("corutine before yield" + moving);
        yield return new WaitForSeconds(0.4f);
        moving = false;
        Debug.Log("corutine after yield" + moving);
    }
}
