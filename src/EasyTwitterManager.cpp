// EasyTwitterManagerCSL.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "..\include\twitcurl.h"

void bonjour()
{
	std::cout << "******************************************" << std::endl;
	std::cout << "********* Easy Twitter Manager ***********" << std::endl;
	std::cout << "******************************************" << std::endl;

	std::cout << "\nEcole ESGI (Paris) | Projet C++ | Annee scolaire 2013/2014\n" << std::endl;
}

int menu()
{
	std::cout << "\n--Menu--" << std::endl;

	std::cout << "\n   1 - choix 1" << std::endl;
	std::cout << "   2 - choix 2" << std::endl;
	std::cout << "   3 - choix 3" << std::endl;
	std::cout << "   4 - choix 4" << std::endl;
	std::cout << "   5 - choix 5" << std::endl;

	int response;
	std::cin >> response; 
	return response;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Message d'accueil
	bonjour();

	system("PAUSE");
	int choix;
	choix = menu();
	/*
	// --- Variables ---
	std::string userName;
	std::string passWord;
	// -----------------

	std::cout << "Login : ";
	std::cin >> userName;

	std::cout << "Mot de passe : ";
	std::cin >> passWord;
	*/

	// --- TWITCURL ---
    twitCurl twitterObj;
    std::string tmpStr, tmpStr2;
    std::string replyMsg;
    char tmpBuf[1024];

    /* Set twitter username and password */
    //twitterObj.setTwitterUsername( userName );
    //twitterObj.setTwitterPassword( passWord );

    /* Set proxy server usename, password, IP and port (if present) */
    memset( tmpBuf, 0, 1024 );
    //printf( "\nDo you have a proxy server configured (0 for no; 1 for yes): " );
	//printf( "\nEst-ce qu'un proxy est configur� ? (0 pour non ; 1 pour oui) : " );
	std::cout << "\nEst-ce que vous disposez d'un proxy (0 pour non; 1 pour oui) : ";
    //gets( tmpBuf );
	std::cin >> tmpBuf;
    tmpStr = tmpBuf;
    if( std::string::npos != tmpStr.find( "1" ) )
    {
        memset( tmpBuf, 0, 1024 );
        printf( "\nAdresse IP du proxy: " );
        std::cin >> tmpBuf;
		//gets( tmpBuf );
        tmpStr = tmpBuf;
        twitterObj.setProxyServerIp( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nPort du proxy: " );
        std::cin >> tmpBuf;
		//gets( tmpBuf );
        tmpStr = tmpBuf;
        twitterObj.setProxyServerPort( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nNom d'utilisateur du proxy: " );
        std::cin >> tmpBuf;
		//gets( tmpBuf );
        tmpStr = tmpBuf;
        twitterObj.setProxyUserName( tmpStr );

        memset( tmpBuf, 0, 1024 );
        printf( "\nMot de passe du proxy: " );
        std::cin >> tmpBuf;
		//gets( tmpBuf );
        tmpStr = tmpBuf;
        twitterObj.setProxyPassword( tmpStr );
    }


    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
    twitterObj.getOAuth().setConsumerKey( std::string( "vlC5S1NCMHHg8mD1ghPRkA" ) );
    twitterObj.getOAuth().setConsumerSecret( std::string( "3w4cIrHyI3IYUZW5O2ppcFXmsACDaENzFdLIKmEU84" ) );

    /* Step 1: Check if we alredy have OAuth access token from a previous run */
    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");
    std::ifstream oAuthTokenKeyIn;
    std::ifstream oAuthTokenSecretIn;

    oAuthTokenKeyIn.open( "../txt/twitterClient_token_key.txt" );
    oAuthTokenSecretIn.open( "../txt/twitterClient_token_secret.txt" );

    memset( tmpBuf, 0, 1024 );
    oAuthTokenKeyIn >> tmpBuf;
    myOAuthAccessTokenKey = tmpBuf;

    memset( tmpBuf, 0, 1024 );
    oAuthTokenSecretIn >> tmpBuf;
    myOAuthAccessTokenSecret = tmpBuf;

    oAuthTokenKeyIn.close();
    oAuthTokenSecretIn.close();

    if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
    {
        /* If we already have these keys, then no need to go through auth again */
        printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

        twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
    else
    {
        /* Step 2: Get request token key and secret */
        std::string authUrl;
		//authUrl = "https://api.twitter.com/oauth/request_token";
        twitterObj.oAuthRequestToken( authUrl );

        /* Step 3: Get PIN  */
        memset( tmpBuf, 0, 1024 );
        printf( "\nEst-ce que vous voulez visiter twitter.com pour obtenir un PIN (0 pour non; 1 pour oui): " );
        std::cin >> tmpBuf;
		//gets( tmpBuf );
        tmpStr = tmpBuf;
        if( std::string::npos != tmpStr.find( "1" ) )
        {
            /* Ask user to visit twitter.com auth page and get PIN */
            memset( tmpBuf, 0, 1024 );
            printf( "\nCopiez-Collez ce lien dans votre navigateur et autorisez l'application :\n%s", authUrl.c_str() );
            printf( "\nEntrez le PIN re�u par Twitter: " );
            std::cin >> tmpBuf;
			//gets( tmpBuf );
            tmpStr = tmpBuf;
            twitterObj.getOAuth().setOAuthPin( tmpStr );
        }
        else
        {
            /* Else, pass auth url to twitCurl and get it via twitCurl PIN handling */
            twitterObj.oAuthHandlePIN( authUrl );
        }

        /* Step 4: Exchange request token with access token */
        twitterObj.oAuthAccessToken();

        /* Step 5: Now, save this access token key and secret for future use without PIN */
        twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

        /* Step 6: Save these keys in a file or wherever */
        std::ofstream oAuthTokenKeyOut;
        std::ofstream oAuthTokenSecretOut;

        oAuthTokenKeyOut.open( "twitterClient_token_key.txt" );
        oAuthTokenSecretOut.open( "twitterClient_token_secret.txt" );

        oAuthTokenKeyOut.clear();
        oAuthTokenSecretOut.clear();

		// Mise a jour des cles d'acces (fichiers txt)
        oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
        oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

		// Fermeture des fichiers
        oAuthTokenKeyOut.close();
        oAuthTokenSecretOut.close();
    }
    /* OAuth flow ends */
	// A ce moment la, CONNEXION ETABLIE

    /* Account credentials verification */
    if( twitterObj.accountVerifyCredGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get followers' ids */
    std::string nextCursor("");
    std::string searchUser("nextbigwhat");
    do
    {
        if( twitterObj.followersIdsGet( nextCursor, searchUser ) )
        {
            twitterObj.getLastWebResponse( replyMsg );
            printf( "\ntwitterClient:: twitCurl::followersIdsGet for user [%s] web response:\n%s\n",
                    searchUser.c_str(), replyMsg.c_str() );

            // JSON: "next_cursor":1422208797779779359,
            nextCursor = "";
            size_t nNextCursorStart = replyMsg.find("next_cursor");
            if( std::string::npos == nNextCursorStart )
            {
                nNextCursorStart += strlen("next_cursor:\"");
                size_t nNextCursorEnd = replyMsg.substr(nNextCursorStart).find(",");
                if( std::string::npos != nNextCursorEnd )
                {
                    nextCursor = replyMsg.substr(nNextCursorStart, (nNextCursorEnd - nNextCursorStart));
                    printf("\nNEXT CURSOR: %s\n\n\n\n\n", nextCursor.c_str());
                }
            }
        }
        else {
            twitterObj.getLastCurlError( replyMsg );
            printf( "\ntwitterClient:: twitCurl::followersIdsGet error:\n%s\n", replyMsg.c_str() );
            break;
        }
    } while( !nextCursor.empty() && nextCursor.compare("0") );

    /* Get block list */
    nextCursor = "";
    if( twitterObj.blockListGet( nextCursor, false, false ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::blockListGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::blockListGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get blocked ids */
    nextCursor = "";
    if( twitterObj.blockIdsGet( nextCursor, true ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::blockIdsGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::blockIdsGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Post a new status message */
    memset( tmpBuf, 0, 1024 );
    printf( "\nEnter a new status message: " );
    gets( tmpBuf );
    tmpStr = tmpBuf;
    replyMsg = "";
    if( twitterObj.statusUpdate( tmpStr ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", replyMsg.c_str() );
    }

    /* Post a new reply */
    memset( tmpBuf, 0, 1024 );
    printf( "\nEnter message id to reply to : " );
    gets( tmpBuf );
    tmpStr2 = tmpBuf;
    memset( tmpBuf, 0, 1024 );
    printf( "\nEnter a reply message: " );
    gets( tmpBuf );
    tmpStr = tmpBuf;
    replyMsg = "";
    if( twitterObj.statusUpdate( tmpStr, tmpStr2 ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", replyMsg.c_str() );
    }


    /* Search a string */
    printf( "\nEnter string to search: " );
    memset( tmpBuf, 0, 1024 );
    gets( tmpBuf );
    tmpStr = tmpBuf;
    printf( "\nLimit search results to: " );
    memset( tmpBuf, 0, 1024 );
    gets( tmpBuf );
    tmpStr2 = tmpBuf;
    replyMsg = "";
    if( twitterObj.search( tmpStr, tmpStr2 ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::search web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::search error:\n%s\n", replyMsg.c_str() );
    }

	std::cin.get();

#ifdef _TWITCURL_TEST_
    /* Get user timeline */
    replyMsg = "";
    printf( "\nGetting user timeline\n" );
    if( twitterObj.timelineUserGet( true, true, 0 ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Destroy a status message */
    memset( tmpBuf, 0, 1024 );
    printf( "\nEnter status message id to delete: " );
    gets( tmpBuf );
    tmpStr = tmpBuf;
    replyMsg = "";
    if( twitterObj.statusDestroyById( tmpStr ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById error:\n%s\n", replyMsg.c_str() );
    }

    /* Get public timeline */
    replyMsg = "";
    printf( "\nGetting public timeline\n" );
    if( twitterObj.timelinePublicGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get friend ids */
    replyMsg = "";
    printf( "\nGetting friend ids\n" );
    tmpStr = "techcrunch";
    if( twitterObj.friendsIdsGet( tmpStr, false ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get trends */
    if( twitterObj.trendsDailyGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet error:\n%s\n", replyMsg.c_str() );
    }
#endif // _TWITCURL_TEST_

    return 0;
}

