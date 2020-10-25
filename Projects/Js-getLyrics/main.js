const BASE_URL = 'https://api.lyrics.ovh/v1/'
const songList = document.querySelector('#song-list')
const lyricsPanel = document.querySelector('#lyrics-panel')
const album = {
  artist: 'Adele',
  album: '25',
  tracks: [
    'Hello',
    'Send My Love (To Your New Lover)',
    'I Miss You',
    'When We Were Young',
    'Remedy',
    'Water Under the Bridge',
    'River Lea',
    'Love in the Dark',
    'Million Years Ago',
    'All I Ask',
    'Sweetest Devotion'
  ]
}

for (let value of album.tracks) {
  const songHtml = `
    <li class="nav-item">
      <a class="nav-link" href="#">${value}</a>
    </li>
  `
  songList.innerHTML += songHtml
}

songList.addEventListener('click', (event) => {
  if (event.target.classList.contains("nav-link")) {
    const allAList = document.querySelectorAll('.nav-item a')
    for (let value of allAList) {
      value.classList.remove('active')
    }
    event.target.classList.toggle("active")
    const song = event.target.innerText
    const url = `${BASE_URL} ${album.artist}/${song}`
    axios.get(url).then((response) => {
      const lyricsHtml = `
        <h2>${song}</h2>
        <pre>${response.data.lyrics}</pre>
        `
      lyricsPanel.innerHTML = lyricsHtml
    }).catch((error) => {
      console.log(error)
    })
  }
})

