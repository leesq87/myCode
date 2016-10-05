using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;


public class wmDragRotation : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{

    public float dragRate = 40;
    
    Vector2 oldPos;
    Vector2 newPos;

    GameObject obj;

    public void OnBeginDrag(PointerEventData eventData)
    {
        if (WorldMapManager.Instance().dragState == false)
        {
            WorldMapManager.Instance().dragState = true;
        }
        oldPos = new Vector2(eventData.position.x, eventData.position.y);
        //Debug.Log("OnBeginDrag");
        
    }
    public void OnDrag(PointerEventData eventData)
    {
        if(WorldMapManager.Instance().dragState == false)
        {
            WorldMapManager.Instance().dragState = true;
        }
        if (Input.touchCount == 1)  //Build Mode
        {

            //Debug.Log("OnDrag");
            newPos = new Vector2(eventData.position.x, eventData.position.y);
            //Debug.Log(eventData.delta);

            GameObject obj = GameObject.Find("DragCamera");
            obj.transform.Rotate(new Vector3(eventData.delta.y / dragRate, -eventData.delta.x / dragRate,0));
            //obj.transform.localRotation = 

        }//Build Mode

    }

    public void OnEndDrag(PointerEventData eventData)
    {
        WorldMapManager.Instance().dragState = true;
        
        //Debug.Log("OnDragEnd");
    }
    
}
