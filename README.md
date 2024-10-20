# WIP
# Problem:
While developing this demo https://hunter-macnab.itch.io/peralez-questions which leans heavily on written text based portrayals to design social interaction gameplay,
Bogged down as writer/game designer needing to manage to different sets of text within:
Obsidian game design vault. 
![image](https://github.com/user-attachments/assets/0fc1a72e-5001-4209-a086-ff9d51d2791f)

UE5 blueprint implementation.
![image](https://github.com/user-attachments/assets/09b0a8d6-e0ee-4536-bc10-80d01aa84c96)


Results in a time consuming messy workflow. The Writer wants to work in Obsidian, but is forced constant need to copy over changes -> error prone, tedious.

Using UE5 string tables reduces some of challange by ensuring specific text is sourced from only one place, but has same issue needing copy over from obsidian to the csv table.

# Soloution Goal
Enable writer to manage one set of text portrayals inside obsidian vault. 

# Soloution:
Have a script go through obsidian files and fine text. Generate/update a UE5 string table on run with changes to text in obsidian. Plugin the text using table ids defined by writer in obsidian using file name.
