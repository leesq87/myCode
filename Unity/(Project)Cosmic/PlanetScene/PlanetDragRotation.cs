using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;


public class PlanetDragRotation : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{


    public float dragRate = 5;

    GameObject obj;
    GameObject RotateBase;

    Vector3 planetRotation = new Vector3(0, 0, 0);

    void Start()
    {
        obj = GameObject.Find("UI");
        RotateBase = GameObject.Find("DragCamera");
    }
    public void OnBeginDrag(PointerEventData eventData)
    {
        //Debug.Log("OnBeginDrag");
        PlanetTouchRay script = obj.GetComponent<PlanetTouchRay>();
        script.dragTrue();
    }
    public void OnDrag(PointerEventData eventData)
    {
        //Debug.Log("OnDrag");
        RotateBase.transform.Rotate(new Vector3(-eventData.delta.y / dragRate, eventData.delta.x / dragRate, 0));
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        //Debug.Log("OnDragEnd");
        PlanetTouchRay script = obj.GetComponent<PlanetTouchRay>();
        script.dragTrue();
    }

    void calculateRotation()
    {
        planetRotation = RotateBase.transform.rotation.eulerAngles;
    }
}
