#ifndef TWITTERGET_H
#define TWITTERGET_H

#include "stdafx.h"
#include "..\include\twitcurl.h"
#include "windows.h"
#include "winHome.h"
#include "winMassFollow.h"
#include <vector>

class twitterGet
{
    
private:    
    std::string replyMsg;
	std::string nextCursor;
	
    
public:

	//void setup(std::string )
 //   {
 //       setUser(userName, passWord);
 //       setConsumer(consumerKey, consumerSecret);
 //       requestToken();
 //   }

	std::string getUserID(string nom)
			{ 
				/* init */
				replyMsg = "";
				extern twitCurl twitterObj;

				/* work */
				if(twitterObj.userGet(nom, false))
				{
					twitterObj.getLastWebResponse( replyMsg );
				}
				else
				{
					replyMsg = "Erreur lors de la récupération de l'ID de l'utilisateur";
				}
				
				unsigned pos = replyMsg.find("id_str"); 
				string afterid = replyMsg.substr(pos+7);
				replyMsg = ExtractString(afterid, "\"", "\"" );
				return replyMsg;
			}

	std::string getAllFollowers(string nom)
			{
				/* init */
				replyMsg = "";
				nextCursor = "";
				extern twitCurl twitterObj;

				/* work */
				string id = getUserID(nom);
				if(twitterObj.followersIdsGet(nextCursor, id, true))
				{
					twitterObj.getLastWebResponse(replyMsg);
					/* get cleaned string with all the ids */
					replyMsg = ExtractString(replyMsg, "[", "]" );
				}
				else
				{
					replyMsg = "Erreur lors de l'exécution de 'followersIdsGet'";
				}
				return replyMsg;
			}

	std::string getUserUsername(string id)
			{ 
				/* init */
				replyMsg = "";
				extern twitCurl twitterObj;

				/* work */
				if(twitterObj.userGet(id, true))
				{
					twitterObj.getLastWebResponse(replyMsg);
				}
				else
				{
					replyMsg = "Erreur lors de la récupération du nom de l'utilisateur";
				}
				
				unsigned pos = replyMsg.find("screen_name"); 
				string afterid = replyMsg.substr(pos+12);
				replyMsg = ExtractString(afterid, "\"", "\"" );
				return replyMsg;
			}

	std::string followByID(string id)
			{
				/* init */
				replyMsg = "";
				extern twitCurl twitterObj;

				/* work */
				if (twitterObj.friendshipCreate(id, true))
				{
					replyMsg = getUserUsername(id);
					return "Follow de @" + replyMsg + " avec succès";
				}
				else
				{
					twitterObj.getLastCurlError( replyMsg );
					return "error";
				}
			}




	
	/* others */
	string ExtractString( std::string source, std::string start, std::string end )
			{
				std::string::size_type startIndex = source.find( start );

				 if( startIndex == std::string::npos )
				 {
					string emptyString = "";
	 				return emptyString;
				 }
				
				 startIndex += start.length();

				 std::string::size_type endIndex = source.find( end, startIndex );

				 return source.substr( startIndex, endIndex - startIndex );
			}
    
};

#endif