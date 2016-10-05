using UnityEngine;
using System.Collections;
using System;
using UnityEngine.Purchasing;

public class cslnAppBilling : MonoBehaviour, IStoreListener
{

    private static IStoreController storeController;
    private static IExtensionProvider extensionProvider;

    #region 상품ID
    // 상품ID는 구글 개발자 콘솔에 등록한 상품ID와 동일하게.
    public const string productId1 = "com.sky.swim.item001";
    #endregion

    void Start()
    {
        InitializePurchasing();
    }

    private bool IsInitialized()
    {
        return (storeController != null && extensionProvider != null);
    }

    public void InitializePurchasing()
    {
        if (IsInitialized())
            return;

        var module = StandardPurchasingModule.Instance();

        ConfigurationBuilder builder = ConfigurationBuilder.Instance(module);

        builder.AddProduct(productId1, ProductType.Consumable, new IDs
            {
                { productId1, AppleAppStore.Name },
                { productId1, GooglePlay.Name },
            });

        //        builder.AddProduct(productId2, ProductType.Consumable, new IDs
        //            {
        //                { productId2, AppleAppStore.Name },
        //                { productId2, GooglePlay.Name }, }
        //        );
        //
        //        builder.AddProduct(productId3, ProductType.Consumable, new IDs
        //            {
        //                { productId3, AppleAppStore.Name },
        //                { productId3, GooglePlay.Name },
        //            });
        //
        //        builder.AddProduct(productId4, ProductType.Consumable, new IDs
        //            {
        //                { productId4, AppleAppStore.Name },
        //                { productId4, GooglePlay.Name },
        //            });
        //
        //        builder.AddProduct(productId5, ProductType.Consumable, new IDs
        //            {
        //                { productId5, AppleAppStore.Name },
        //                { productId5, GooglePlay.Name },
        //            });

        UnityPurchasing.Initialize(this, builder);
    }

    public void BuyProduct1()
    {
        BuyProductID(productId1);
    }

    public void BuyProductID(string productId)
    {
        try
        {
            if (IsInitialized())
            {
                Product p = storeController.products.WithID(productId);

                if (p != null && p.availableToPurchase)
                {
                    Debug.Log(string.Format("Purchasing product asychronously: '{0}'", p.definition.id));
                    storeController.InitiatePurchase(p);
                }
                else
                {
                    Debug.Log("BuyProductID: FAIL. Not purchasing product, either is not found or is not available for purchase");
                }
            }
            else
            {
                Debug.Log("BuyProductID FAIL. Not initialized.");
            }
        }
        catch (Exception e)
        {
            Debug.Log("BuyProductID: FAIL. Exception during purchase. " + e);
        }
    }

    public void RestorePurchase()
    {
        if (!IsInitialized())
        {
            Debug.Log("RestorePurchases FAIL. Not initialized.");
            return;
        }

        if (Application.platform == RuntimePlatform.IPhonePlayer || Application.platform == RuntimePlatform.OSXPlayer)
        {
            Debug.Log("RestorePurchases started ...");

            var apple = extensionProvider.GetExtension<IAppleExtensions>();

            apple.RestoreTransactions
            (
                (result) => { Debug.Log("RestorePurchases continuing: " + result + ". If no further messages, no purchases available to restore."); }
            );
        }
        else
        {
            Debug.Log("RestorePurchases FAIL. Not supported on this platform. Current = " + Application.platform);
        }
    }

    public void OnInitialized(IStoreController sc, IExtensionProvider ep)
    {
        Debug.Log("OnInitialized : PASS");

        storeController = sc;
        extensionProvider = ep;
    }

    public void OnInitializeFailed(InitializationFailureReason reason)
    {
        Debug.Log("OnInitializeFailed InitializationFailureReason:" + reason);
    }

    public PurchaseProcessingResult ProcessPurchase(PurchaseEventArgs args)
    {
        Debug.Log(string.Format("ProcessPurchase: PASS. Product: '{0}'", args.purchasedProduct.definition.id));

        switch (args.purchasedProduct.definition.id)
        {
            case productId1:

                int tempNum = 10000;
                string Query;
                // ex) gem 10개 지급
                if (GameObject.Find("GameManager").GetComponent<MainSingleTon>())
                {
                    MainSingleTon.Instance.cPE += tempNum;
                    Query = "UPDATE userTable SET cPE = " + MainSingleTon.Instance.cPE;
                    GameObject.Find("GameManager/SqlManager").GetComponent<MainSceneSQL>().UpdateQuery(Query);

                }
                if (GameObject.Find("GameManager").GetComponent<PlanetSceneSingleTon>())
                {
                    PlanetSceneSingleTon.Instance.cPE += tempNum;
                    Query = "UPDATE userTable SET cPE = " + PlanetSceneSingleTon.Instance.cPE;
                    GameObject.Find("GameManager/SqlManager").GetComponent<MainSceneSQL>().UpdateQuery(Query);
                }




                break;

                //        case productId2:
                //
                //            // ex) gem 50개 지급
                //
                //            break;
                //
                //        case productId3:
                //
                //            // ex) gem 100개 지급
                //
                //            break;
                //
                //        case productId4:
                //
                //            // ex) gem 300개 지급
                //
                //            break;
                //
                //        case productId5:
                //
                //            // ex) gem 500개 지급
                //
                //            break;
        }

        return PurchaseProcessingResult.Complete;
    }

    public void OnPurchaseFailed(Product product, PurchaseFailureReason failureReason)
    {
        Debug.Log(string.Format("OnPurchaseFailed: FAIL. Product: '{0}', PurchaseFailureReason: {1}", product.definition.storeSpecificId, failureReason));
    }
}
