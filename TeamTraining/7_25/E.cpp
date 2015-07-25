#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
      
using namespace std;  
      
int main(){  
        int t;  
        cin>>t;  
        int cas=0;  
        while(t--){  
		cas++;  
		int ans=0;  
		for(int i=1;i<=24;i++){  
			char color[2];  
			scanf("%s",color);  
			if(color[0]=='w'||color[0]=='y'){
				switch(i){  
				case 5:  
				case 7:  
				case 9:  
				case 12:  
				case 14:  
				case 16:  
				case 21:  
				case 24:  
					ans++;  
					break;  
				case 6:  
				case 8:  
				case 10:  
				case 11:  
				case 13:  
				case 15:  
				case 22:  
				case 23:  
					ans+=2;  
					break;  
				}
				cout << i << " " << 
			}  
		}  
		printf("Case #%d: ",cas);  
		if(ans%3==0){  
			printf("YES\n");  
		}else{  
			printf("NO\n");  
		}  
        }  
        return 0;  
}  
