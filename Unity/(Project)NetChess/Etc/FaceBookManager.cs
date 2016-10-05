using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
//Facebook namespace
using Facebook.Unity;
using UnityEngine.UI;
using Facebook.MiniJSON;

public class FaceBookManager : MonoBehaviour {


    public GameObject PhotonManager;
    public Text resTest;

    public string UserID = null;

    // Awake function from Unity's MonoBehavior
    void Awake()
    {
        if (!FB.IsInitialized)
        {
            // Initialize the Facebook SDK
            FB.Init(InitCallback, OnHideUnity);
        }
        else
        {
            // Already initialized, signal an app activation App Event
            FB.ActivateApp();
        }
    }


    private void InitCallback()
    {
        if (FB.IsInitialized)
        {
            // Signal an app activation App Event
            FB.ActivateApp();
            // Continue with Facebook SDK
            // ...
        }
        else
        {
            Debug.Log("Failed to Initialize the Facebook SDK");
        }
    }

    private void OnHideUnity(bool isGameShown)
    {
        if (!isGameShown)
        {
            // Pause the game - we will need to hide
            Time.timeScale = 0;
        }
        else
        {
            // Resume the game - we're getting focus again
            Time.timeScale = 1;
        }
    }


    List<string> perms = new List<string>() { "public_profile", "email", "user_friends" };
    
    public void FBLogin()
    {
        FB.LogInWithReadPermissions(perms, AuthCallback);

    }

    private void AuthCallback(ILoginResult result)
    {
        Debug.Log(result);
        if (FB.IsLoggedIn)
        {
            // AccessToken class will have session details
            AccessToken aToken = Facebook.Unity.AccessToken.CurrentAccessToken;
            // Print current access token's User ID
            Debug.Log(aToken.UserId);
            
            // Print current access token's granted permissions

            

          
            FB.API("/me?fields=name", HttpMethod.GET, UserCallBack);

            
            foreach (string perm in aToken.Permissions)
            {
                Debug.Log(perm);
            }
        }
        else
        {
            Debug.Log("User cancelled login");
        }
    }

    private void UserCallBack(IResult result)
    {

        if(result.Error == null)
        {
            UserID = result.ResultDictionary["name"] as string;
            Debug.Log("유저아이디 : "+UserID);
            PhotonManager.GetComponent<MainPhotonInit>().FacebookLogin(UserID);
        }
        else
        {
            Debug.Log(result.Error);
        }
    }
}




    //    private bool _isSessionOpen = false;

    //    private Texture2D _imageTexture = null;
    //    string resultPrint = "";

    //    //for calculate screen size
    //    int _safeWidth = 0;
    //    int _safeHeight = 0;

    //    void Start()
    //    {
    //        _safeWidth = Screen.width - 20;
    //        _safeHeight = Screen.height - 190;
    //    }

    //    void Update()
    //    {

    //    }

    //    public void FBLogin()
    //    {
    //        // Login button
    //        if (!_isSessionOpen)
    //        {
    //            FacebookLogin();
    //        }

    //        //profile image display after login
    //        if (_imageTexture != null
    //            && _isSessionOpen == true)
    //        {
    //            GUI.DrawTexture(
    //                new Rect(10, 110, 50, 50),
    //                _imageTexture);
    //        }

    //        // print result or error
    //        if (resultPrint.Length > 2)
    //        {
    //            GUI.Label(
    //                new Rect(10, 170, _safeWidth, _safeHeight),
    //                resultPrint);
    //        }
    //    }

    //    void FacebookLogin()
    //    {
    //#if UNITY_ANDROID
    //        try
    //        {
    //            using (AndroidJavaClass jc =
    //                new AndroidJavaClass("com.unity3d.player.UnityPlayer"))
    //            {
    //                using (AndroidJavaObject jo =
    //                    jc.GetStatic<AndroidJavaObject>("currentActivity"))
    //                {
    //                    Debug.Log("facebook login");

    //                    jo.Call("FacebookLogin");

    //                }
    //            }
    //        }
    //        catch (Exception e)
    //        {
    //            Debug.Log(e.StackTrace);
    //        }
    //#endif
    //    }

    //    void didLogin(string id)
    //    {
    //        _isSessionOpen = true;
    //        StartCoroutine(LoadProfileImage(id));
    //        StartCoroutine(LoadYourFacebookData(id));
    //    }

    //    void errorPrint(string error)
    //    {
    //        resultPrint = error;
    //    }

    //    private IEnumerator LoadProfileImage(string id)
    //    {
    //        WWW imageRequest =
    //         new WWW("http://graph.facebook.com/" + id + "/picture");
    //        yield return imageRequest;
    //        if (imageRequest.isDone)
    //        {
    //            _imageTexture = imageRequest.texture;
    //        }
    //    }

    //    private IEnumerator LoadYourFacebookData(string id)
    //    {
    //        WWW fbDataRequest =
    //            new WWW("http://graph.facebook.com/" + id);
    //        yield return fbDataRequest;
    //        if (fbDataRequest.isDone)
    //        {
    //            resultPrint = fbDataRequest.text;
    //        }
    //    }

