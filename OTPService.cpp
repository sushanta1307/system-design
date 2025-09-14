#include<iostream>
#include<unordered_map>
#include<ctime>
// #include<chrono>

using namespace std;
// using namespace std::chrono;

class OTP {
public:
    string code;
    long expiryTime;
    int attempts;
    OTP(){}
    OTP(string cd, long t, int at) : code(cd), expiryTime(t), attempts(at) {}
};

class OTPGenerator {
public:
    string generate() {
        // srand(time(NULL));
        string otp = "";
        for(int i=0;i<6;i++) {
            otp += to_string(rand()%10);
        }

        return otp;
    }
};

class OTPRepository {
    unordered_map<string, OTP> store; // key: userId
public:
    void saveOTP(string userId, OTP otp) {
        store[userId] = otp;
    }

    void deleteOTP(string userId) {
        store.erase(userId);
    }

    OTP* getOTP(string userId) {
        return store.count(userId) ? &store[userId] : NULL;
    }
};

class OTPChannel {
public:
    virtual void send(string userId, string otp) = 0;

};

class SMSChannel : public OTPChannel{
public:
    void send(string userId, string otp) {
        cout<<"Sending OTP :" << otp << " for User Id: " << userId << " via SMS" << endl;
    }
};

class EmailChannel : public OTPChannel{
public:
    void send(string userId, string otp) {
        cout<<"Sending OTP: " << otp << " for User Id: " << userId << " via email" << endl;
    }
};

class OTPService {
    OTPGenerator generator;
    OTPRepository repo;
    OTPChannel* channel;

public:
    OTPService(OTPChannel* c) : channel(c) {}

    void generateOTP(string userId) {
        string code = generator.generate();
        // auto t = chrono::system_clock::now() + minutes(5);
        // long millis = chrono::duration_cast<milliseconds>(t.time_since_epoch()).count();
        long millis = time(NULL) + 300;
        OTP otp = {code, millis, 0};
        repo.saveOTP(userId, otp);
        channel->send(userId, code);

    }

    bool validateOTP(string userId, string code) {
        OTP* otp = repo.getOTP(userId);
        if(!otp) return false;
        // if(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() > otp->expiryTime)
        //     return false;
        if(time(NULL) > otp->expiryTime) return false;
        if(otp->attempts >= 3) return false;
        otp->attempts++;
        if(otp->code == code) {
            repo.deleteOTP(userId);
            return true;
        }

        return false;
    }

};

int main() {
    OTPChannel *ch = new EmailChannel();
    OTPService otpService(ch);
    otpService.generateOTP("123");
    if(otpService.validateOTP("123", "793802")) {
        cout<<"OTP validated Successfully"<<endl;
    } else {
        cout<<"Invalid OTP, try again!"<<endl;
    }
    return 0;
}