#ifndef __Demo__MTNotificationQueue__  
#define __Demo__MTNotificationQueue__  

#include "cocos2d.h"  
#include <pthread.h>  
#include <vector>  

using namespace cocos2d;  
using namespace std;  

class CNotificationQueue : public Ref {

public:  

	static CNotificationQueue* sharedInstance();  

	void postNotifications(float in_fDeltaTime);  

	void postNotification(const char* in_pArrCharName, Ref* in_pCcObj);

	void cleanVecNotifications();

private:  

	CNotificationQueue();  

	~CNotificationQueue();  

private:  

	static CNotificationQueue* sm_pInstance;  

	class CGarbo {  
	public:  
		~CGarbo() {  
			if (CNotificationQueue::sm_pInstance) {  
				delete CNotificationQueue::sm_pInstance;  
			}  
		}  
	};  

	static CGarbo sm_oCGarbo;  

	typedef struct {  
		string m_oStrName;  
		Ref* m_pCcObj;
	} NotificationArgs;  

	vector<NotificationArgs> m_oVecNotifications;  
};  

#endif