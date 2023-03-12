from pytube import YouTube
from sys import argv

link = argv[1]
resolution = argv[2]
yt = YouTube(link)

video_resolutions = []
videos = []
    
print ("title: ", yt.title)
print("Views: ", yt.views)
for stream in yt.streams.order_by('resolution'):
    # print(stream)
    video_resolutions.append(stream.resolution)
    videos.append(stream)

print(video_resolutions)

     
yd = yt.streams.get_by_resolution(resolution) # https://www.youtube.com/watch?v=H5WM2NabiUc 720
yd.download('/mnt/c/Videos')