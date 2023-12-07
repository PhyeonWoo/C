window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "상계 백병원\n", lat: 37.648503, lng: 127.063142, phone: "전화번호 : 02-950-1144\n",
          time: "진료시간 : 월~금 08:30 ~ 17:00\n", details: "상세정보 : 서울 노원구 동일로 1342"},

        { label: "B", name: "원자력 병원\n", lat: 37.628784, lng: 127.0826588, phone: "전화번호 : 02-970-2114\n", 
          time: "진료시간 : 월~금 09:00 ~ 17:00\n",details: "상세정보 : 서울 노원구 노원로 75\n"},

        { label: "C", name: "노원 을지대학병원\n", lat: 37.636440, lng: 127.070009, phone: "전화번호 : 1899-0001\n",
         time: "진료시간 : 월~금 08:30 ~ 17:30\n",details:"상세정보 :서울 노원구 한글비석로 68"},

        { label: "D", name: "한일병원\n", lat: 37.6458568, lng: 127.0285789, phone: "전화번호 : 02-901-3114\n",
         time: "진료시간 : 월~금 08:30 ~ 17:30\n",details:"상세정보 : 서울 도봉구 우이천로 308"},

        { label: "E", name: "대한병원\n", lat: 37.6352594 , lng: 127.0228979 , phone: "전화번호 : 02-903-3231\n",
        time: "진료시간 : 월~금 09:00 ~ 18:00\n",details:"상세정보 : 서울 강북구 도봉로 301"},
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
