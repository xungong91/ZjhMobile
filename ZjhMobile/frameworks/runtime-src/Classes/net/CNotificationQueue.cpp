#include "CNotificationQueue.h"

pthread_mutex_t sharedNotificationQueueLock;  

class LifeManager_PThreadMutex {  

private:  

	pthread_mutex_t* m_pMutex;  

public:  

	LifeManager_PThreadMutex(pthread_mutex_t* in_pMutex) : m_pMutex(in_pMutex) {  
		pthread_mutex_init(m_pMutex, NULL);  
	}  

	~LifeManager_PThreadMutex() {  
		pthread_mutex_destroy(m_pMutex);  
	}  

}__LifeManager_sharedNotificationQueueLock(&sharedNotificationQueueLock);  

class LifeCircleMutexLocker {  

private:  

	pthread_mutex_t* m_pMutex;  

public:  

	LifeCircleMutexLocker(pthread_mutex_t* in_pMutex) : m_pMutex(in_pMutex) {  
		pthread_mutex_lock(m_pMutex);  
	}  

	~LifeCircleMutexLocker() {  
		pthread_mutex_unlock(m_pMutex);  
	}  
};  

#define LifeCircleMutexLock(mutex) LifeCircleMutexLocker __locker__(mutex)  


CNotificationQueue* CNotificationQueue::sm_pInstance = NULL;  
CNotificationQueue::CGarbo CNotificationQueue::sm_oCGarbo;
CNotificationQueue* CNotificationQueue::sharedInstance() {  
	if (!sm_pInstance) {  
		sm_pInstance = new CNotificationQueue();  
	}  
	return sm_pInstance;  
}  

CNotificationQueue::CNotificationQueue() {}  

CNotificationQueue::~CNotificationQueue()
{
	sm_pInstance=NULL;
}  

void CNotificationQueue::cleanVecNotifications()
{
	//delete notify
	for (auto it : m_oVecNotifications)
	{
		it.m_pCcObj = NULL;
		CC_SAFE_RELEASE(it.m_pCcObj);
	}
	m_oVecNotifications.clear();
}

void CNotificationQueue::postNotifications(float in_fDeltaTime) {  
	LifeCircleMutexLock(&sharedNotificationQueueLock);  

    __NotificationCenter* t_pNotiCenter = __NotificationCenter::getInstance();
	for (uint16_t i = 0; i < m_oVecNotifications.size(); i ++)
    {
		NotificationArgs& tmp_oNotiArgs = m_oVecNotifications[i];
		t_pNotiCenter->postNotification(tmp_oNotiArgs.m_oStrName.c_str(), tmp_oNotiArgs.m_pCcObj);  
	}  
	m_oVecNotifications.clear();  
}  

void CNotificationQueue::postNotification(const char* in_pArrCharName, Ref* in_pCcObj) {
	LifeCircleMutexLock(&sharedNotificationQueueLock);  

	NotificationArgs t_oNotiArgs;  
	t_oNotiArgs.m_oStrName = in_pArrCharName;  

	if (in_pCcObj) {  
		t_oNotiArgs.m_pCcObj = in_pCcObj;   // object->copy();  
	} else {  
		t_oNotiArgs.m_pCcObj = NULL;  
	}
	m_oVecNotifications.push_back(t_oNotiArgs);  
}  