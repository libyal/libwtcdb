# Script that synchronizes the local test data
#
# Version: 20251217

$Repository = "dfirlabs/greendale-specimens"
$TestDataPath = "wtcdb/student-pc1"
$TestSet = "public"
$TestInputDirectory = "tests/input"
$TestFiles = "thumbcache_256.db thumbcache_idx.db"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$Url = "https://raw.githubusercontent.com/${Repository}/refs/heads/main/${TestDataPath}/${TestFile}"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

