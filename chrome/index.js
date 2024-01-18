// 토글 버튼
const toggleButton = document.querySelector(".toggle-button");

// body
const body = document.querySelector("body");

// header > ul
const header = document.querySelector(".header-nav-list-wrapper");


// searchInput
const searchInput = document.querySelector(".search-input");

const bookmarkSection = document.querySelector(".bookmark-section");

// List 
const bookmarkList = ['daum','kakao','naver','zum','samsung'];

for(let i = 0; i<bookmarkList.length; i++) {    
    const bookmark = document.createElement('a');
    bookmark.classList.add("bookmark-item");

    const div1 = document.createElement('div');
    div1.classList.add("img-icon-wrapper");
    const img = document.createElement('img');
    img.setAttribute("src", "./images/" + bookmarkList[i] + ".png");
    div1.appendChild(img);

    //div2
    const div2 = document.createElement('div');
    div2.classList.add("bookmark-text");
    div2.textContent = bookmarkList[i];

    //
    bookmark.appendChild(div1);
    bookmark.appendChild(div2);

    bookmarkSection.appendChild(bookmark);  
}



toggleButton.addEventListener("click", () => {
    
    // bookmarkText
    const bookmarkText = document.querySelectorAll(".bookmark-text");
    
    toggleButton.classList.toggle("toggle-button-darkmode");
    body.classList.toggle("body-background-darkmode");
    header.classList.toggle("text-darkmode");
    for(let i = 0; i<bookmarkText.length; i++) {
        bookmarkText[i].classList.toggle("text-darkmode");
    }

    if(toggleButton.classList.contains("toggle-button-darkmode")) {
        toggleButton.textContent = "일반 모드";
    }else{
        toggleButton.textContent = "다크 모드";
    }
});