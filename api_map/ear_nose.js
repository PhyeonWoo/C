window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "하나 이비인후과의원\n", lat: 37.653842, lng: 127.0602611, phone: "전화번호 : 02-952-8883\n",
          time: "진료시간 : 월~금 09:00 ~ 19:30\n", details: "상세정보 : 서울 노원구 동일로 1405 노원프라자 5층"},

        { label: "B", name: "삼성드림 이비인후과의원\n", lat: 37.654232, lng: 127.0617, phone: "전화번호 : 02-935-1365\n", 
          time: "진료시간 : 월~금 09:00 ~ 18:30\n",details: "상세정보 : 서울 노원구 노해로 482 덕영빌딩 4층\n"},

        { label: "C", name: "이병희 이빈이후과의원\n", lat: 37.6519425, lng: 127.0615701, phone: "전화번호 : 02-931-4144\n",
         time: "진료시간 : 월~금 09:00 ~ 18:30\n",details:"상세정보 : 서울 노원구 동일로 1382 올림피아상가 201"},

        { label: "D", name: "선 이비인후과의원\n", lat: 37.6519425, lng: 127.0615701, phone: "전화번호 : 02-931-3090\n",
         time: "진료시간 : 월~금 09:00 ~ 18:00\n",details:"상세정보 : 서울 노원구 동일로 1380 메디칼빌딩 2층"},

        { label: "E", name: "닥터오 이비인후과의원\n", lat: 37.6459658, lng: 127.0641536, phone: "전화번호 : 02-6956-0863\n",
        time: "진료시간 : 월~금 09:00 ~ 19:00\n",details:"상세정보 : 서울 노원구 동일로 1308 정안프라자 2층"},
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
            infoWindow.setContent(`<strong>${name}</strong><br>${phone}<br>${time}<br>${details}`);
            infoWindow.open({
                anchor: marker,
                map
            });
        });
    });

    map.fitBounds(bounds);
};
