Rails.application.config.middleware.use OmniAuth::Builder do
	provider :github, Settings.github.consumer_key, Settings.github.consumer_secret, scope: "user,repo,gist"
end