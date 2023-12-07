window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "삼성편한내과\n", lat: 37.651685, lng: 127.061651, phone: "전화번호 : 02-934-7500\n",
          time: "진료시간 : 월~금 08:30 ~ 18:00\n", details: "서울 노원구 동일로 1380 메디칼빌딩 4층"},

        { label: "B", name: "상계 맑은내과의원\n", lat: 37.650503, lng: 127.061960, phone: "전화번호 : 02-930-7616\n", 
          time: "진료시간 : 월~금 09:00 ~ 16:30\n",details: "상세정보 : 서울 노원구 동일로 1366 삼봉빌딩 5층\n"},

        { label: "C", name: "천내과\n", lat: 37.648443, lng: 127.061959, phone: "전화번호 : 02-3296-3311\n",
         time: "진료시간 : 월,화,수,금 09:00 ~ 18:00\n",details:"서울 노원구 동일로 1343 동일프라자 301호"},

        { label: "D", name: "연세내과\n", lat: 37.654387, lng: 127.062681, phone: "전화번호 : 02-952-6671\n",
         time: "진료시간 : 월~금 09:00 ~ 17:30\n",details:"서울 노원구 동일로 1396 중원빌딩 2층"},
        
        { label: "E", name: "윤내과의원\n", lat:37.6566642, lng: 127.0625976, phone: "전화번호 : 02-934-7575\n",
        time: "진료시간 : 월~금 09:00 ~ 18:00\n",details:"서울 노원구 상계로3길 10"},

        { label: "F",name:"건강미소 내과의원\n", lat: 37.6541645, lng: 127.0614033, phone: "전화번호 : 02-931-5513\n",
        time: "진료시간 : 월~금 08:30 ~ 19:00\n",details: "서울 노원구 노해로 480 5층"},
    ];
    const bounds = new google.maps.LatLngBounds();
    const infoWindow = new google.maps.InfoWindow();
    
    malls.forEach(({ label, name, lat, lng, phone,time,details }) => {
        const marker = new google.maps.Marker({
            position: { lat, lng },
            label,
            map
        });
        bounds.extend(marker.position);
        
        marker.addListener("click", () => {
            map.panTo(marker.position);
            infoWindow.setContent(`<strong><span style="font-size:18px;">${name}</strong><br><span style="font-size:13px;">${phone}<br><span style="font-size:13px;">${time}<br><span style="font-size:13px;">${details}`);
            infoWindow.open({
                anchor: marker,
                map
            });
        });
    });

    map.fitBounds(bounds);
};
  