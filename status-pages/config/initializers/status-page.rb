StatusPage.configure do
  self.use :database
  #self.interval = 40
 #  self.error_callback = proc do |e|
	#   logger.error "Health check failed with: #{e.message}"
	#   Raven.capture_exception(e)
	# end

end
